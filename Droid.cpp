#include "Droid.h"
#include "Math.h"

#include <SoftwareSerial.h>
#include <UbxGpsNavPvt.h>

SoftwareSerial _ss(GPS_TX, GPS_RX);
UbxGpsNavPvt<SoftwareSerial> _gps(_ss);

void Motor::Setup(int in1, int in2, int en) {
  _in1 = in1;
  _in2 = in2;
  _en = en;

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en, OUTPUT);
}

void Motor::Set(int speed, boolean reverse) {
  analogWrite(_en, speed);
  digitalWrite(_in1, !reverse);
  digitalWrite(_in2, reverse);
}

void Droid::Setup() {
  Object::Setup();

  _pidSpeed.configure(0.1, 0.5, 0.1, 10, 8, false);
  _pidHeading.configure(0.1, 0.5, 0.1, 10, 8, false);

  _gps.begin(GPS_BAUDRATE);
  _current = 0;
  
  _leftMotor.Setup(IN1, IN2, EN1);
  _rightMotor.Setup(IN3, IN4, EN2);
  _left = 0;
  _right = 0;
}

void Droid::Update() {
  Object::Update();

  if (millis() - _lastUpdate >= 100) {
    _lastUpdate = millis();
    FetchData();
    Control();
  }

  if (millis() - _lastSend >= UPDATE_INTERVAL) {
    _lastSend = millis();
    Ping();
  }

  while (_network->available()) {
    RF24NetworkHeader header;
    _network->peek(header);
    switch(header.type){
      default:
        break;
      case MSG_ADD_WAYPOINT:
      {
        Point point;
        _network->read(header, &point, sizeof(point));
        for (int i = 0; i < MAX_WAYPOINTS; i++) {
          if (_waypoints[i] == NULL) {
            _waypoints[i] = &point;
            break;
          }
        }
        break;
      }
      case MSG_REP_WAYPOINT:
      {
        Point point;
        _network->read(header, &point, sizeof(point));
        for (int i = 0; i < MAX_WAYPOINTS; i++) {
          _waypoints[i] = NULL;
        }
        _waypoints[0] = &point;
        _current = 0;
        break;
      }
    }
  }
}

void Droid::FetchData() {
  int sensorValue = analogRead(VD_PIN);
  _data.Battery = map(
    sensorValue * (5.0 / 1024) * ((VD_R1 + VD_R2) / VD_R2),
    BATT_MIN,
    BATT_MAX,
    0,
    100
  );
  
  while (_gps.ready()) {
    _data.Latitude = _gps.lon / 10000000.0;
    _data.Longitude = _gps.lat / 10000000.0;
    _data.Speed = _gps.gSpeed * 0.0036; // Convert mm/s to KPH
    _data.Heading = _gps.heading / 100000.0;
    _data.Altitude = _gps.hMSL / 100.0; // Convert mm to m
    _data.NumSatellites  = _gps.numSV;
    _data.Accuracy = _gps.pDOP;
  }
}

void Droid::Control() {
  if (_current >= MAX_WAYPOINTS || _waypoints[_current] == NULL)
    return;

  double distance = calculateDistance(_data.Latitude, _data.Longitude, _waypoints[_current]->Latitude, _waypoints[_current]->Longitude);
  _data.Distance = distance;
  if (distance < TURNING_RADIUS) {
    Serial.println("Moving to next waypoint...");
    _current++;
  }

  if (_current >= MAX_WAYPOINTS || _waypoints[_current] == NULL) {
    Serial.println("Mission complete, halting...");
    _mesh->write(0, 0, MSG_COMPLETE, sizeof(0));
    _left = 0;
    _right = 0;
    _rightMotor.Set(0, false);
    _leftMotor.Set(0, false);
    return;
  }

  double desiredHeading = calculateHeading(_data.Latitude, _data.Longitude, _waypoints[_current]->Latitude, _waypoints[_current]->Longitude);
  
  // Handle 359 -> 0 and 0 -> 359 degrees
  double heading = _data.Heading;
  if (abs(desiredHeading - heading) > 180) {
    if (desiredHeading < heading)
      desiredHeading += 360;
    else
      heading += 360;
  }
  
  uint8_t s = _pidSpeed.step(TARGET_SPEED, _data.Speed);
  _left += s;
  _right += s;
  
  uint8_t h = _pidHeading.step(desiredHeading, _data.Heading);
  _left += h;
  _right -= h;

  _leftMotor.Set(abs(_left), _left < 0);
  _rightMotor.Set(abs(_right), _right < 0);
}

void Droid::Ping() {  
  if (!_mesh->write(0, &_data, MSG_PING, sizeof(_data))) {
    Serial.println("Write fail");
    if (!_mesh->checkConnection()) {
      Serial.println("Renewing address");
      _mesh->renewAddress();
    } else
      Serial.println("Test OK");
  }
}
