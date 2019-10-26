#include "Droid.h"
#include "MathHelper.h"

Droid::Droid(int nodeId)
    : Object(nodeId)
{
}

void Droid::Setup()
{
  Object::Setup();

  _pidSpeed.configure(0.1, 0.5, 0.1, 10, 8, false);
  _pidHeading.configure(0.1, 0.5, 0.1, 10, 8, false);

  _ss = new SoftwareSerial(_gpsTx, _gpsRx);
  _gps = new UbxGpsNavPvt<SoftwareSerial>(*_ss);
  _gps->begin(_gpsBaudrate);
  _current = 0;

  _left = 0;
  _right = 0;
}

void Droid::Update()
{
  Object::Update();

  if (millis() - _lastUpdate >= _controlInterval)
  {
    _lastUpdate = millis();
    FetchData();
    Control();
  }

  if (millis() - _lastSend >= _updateInterval)
  {
    _lastSend = millis();
    Ping();
  }

  while (_network->available())
  {
    RF24NetworkHeader header;
    _network->peek(header);
    switch (header.type)
    {
    default:
      break;
    case MSG_ADD_WAYPOINT:
    {
      Point point;
      _network->read(header, &point, sizeof(point));
      _waypoints.add(&point);
      break;
    }
    case MSG_REP_WAYPOINT:
    {
      Point point;
      _network->read(header, &point, sizeof(point));
      _waypoints.clear();
      _waypoints.add(&point);
      _current = 0;
      break;
    }
    }
  }
}

void Droid::FetchData()
{
  int sensorValue = analogRead(_vdPin);
  _data.Battery = map(
      sensorValue * (5.0 / 1024) * ((_vdR1 + _vdR2) / _vdR2),
      _battMin,
      _battMax,
      0,
      100);

  while (_gps->ready())
  {
    _data.Latitude = _gps->lon / 10000000.0;
    _data.Longitude = _gps->lat / 10000000.0;
    _data.Speed = _gps->gSpeed * 0.0036; // Convert mm/s to KPH
    _data.Heading = _gps->heading / 100000.0;
    _data.Altitude = _gps->hMSL / 100.0; // Convert mm to m
    _data.NumSatellites = _gps->numSV;
    _data.Accuracy = _gps->pDOP;
  }
}

void Droid::Control()
{
  if (_current >= _waypoints.size())
    return;
  
  Point* waypoint = _waypoints.get(_current);
  double distance = calculateDistance(_data.Latitude, _data.Longitude, waypoint->Latitude, waypoint->Longitude);
  _data.Distance = distance;
  if (distance < _turningRadius)
  {
    Serial.println("Moving to next waypoint...");
    _current++;
    waypoint = _waypoints.get(_current);
  }

  if (_current >= _waypoints.size())
  {
    Serial.println("Mission complete, halting...");
    _mesh->write(0, 0, MSG_COMPLETE, sizeof(0));
    _left = 0;
    _right = 0;
    return;
  }

  double desiredHeading = calculateHeading(_data.Latitude, _data.Longitude, waypoint->Latitude, waypoint->Longitude);

  // Handle 359 -> 0 and 0 -> 359 degrees
  double heading = _data.Heading;
  if (abs(desiredHeading - heading) > 180)
  {
    if (desiredHeading < heading)
      desiredHeading += 360;
    else
      heading += 360;
  }

  uint8_t s = _pidSpeed.step(_targetSpeed, _data.Speed);
  _left += s;
  _right += s;

  uint8_t h = _pidHeading.step(desiredHeading, _data.Heading);
  _left += h;
  _right -= h;

  for (int i = 0; i < _components.size(); i++)
    _components.get(i)->Update(_left, _right, &_data);
}

void Droid::Ping()
{
  if (!_mesh->write(0, &_data, MSG_PING, sizeof(_data)))
  {
    Serial.println("Write fail");
    if (!_mesh->checkConnection())
    {
      Serial.println("Renewing address");
      _mesh->renewAddress();
    }
    else
      Serial.println("Test OK");
  }
}

void Droid::AddComponent(Component *component)
{
  if (_components.size() >= _maxComponents)
    Serial.println("Unable to add new component, try increasing MAX_COMPONENTS");
  else
    _components.add(component);
}
