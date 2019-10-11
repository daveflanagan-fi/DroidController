#include "Droid.h"
#include "Math.h"

void Motor::Setup(int in1, int in2, int en) {
  _in1 = in1;
  _in2 = in2;
  _en = en;

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en, OUTPUT);
}

void Motor::Set(int speed, boolean reverse) {
  digitalWrite(_en, speed);
  digitalWrite(_in1, !reverse);
  digitalWrite(_in2, reverse);
}

void Droid::Setup() {
  Object::Setup();

  _pidSpeed.configure(0.1, 0.5, 0.1, 10, 8, false);
  _pidHeading.configure(0.1, 0.5, 0.1, 10, 8, false);
  
#if BOARD_VERSION == 1
  _leftMotor.Setup(IN1, IN2, 2);
  _rightMotor.Setup(IN3, IN4, 2);
#else
  _leftMotor.Setup(IN1, IN2, EN1);
  _rightMotor.Setup(IN3, IN4, EN2);
  _left = 0;
  _right = 0;
#endif
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
        break;
      }
    }
  }
}

void Droid::FetchData() {
  
}

void Droid::Control() {  
  if (_waypoints[0] == NULL)
    return;

  double distance = calculateDistance(_data.Latitude, _data.Longitude, _waypoints[0]->Latitude, _waypoints[0]->Longitude);
  if (distance < TURNING_RADIUS) {
    for (int i = 0; i < MAX_WAYPOINTS - 1; i++) {
      _waypoints[i] = _waypoints[i + 1];
    }
    _waypoints[MAX_WAYPOINTS - 1] = NULL;
  }

  if (_waypoints[0] == NULL) {
    _mesh->write(0, MSG_COMPLETE, sizeof(0));
    _left = 0;
    _right = 0;
    _rightMotor.Set(0, false);
    _leftMotor.Set(0, false);
    return; // Finished waypoint list
  }

  double desiredHeading = calculateHeading(_data.Latitude, _data.Longitude, _waypoints[0]->Latitude, _waypoints[0]->Longitude);
  
#if BOARD_VERSION == 1
  if (desiredHeading < _data.Heading) {
    _rightMotor.Set(255, true);
    _leftMotor.Set(255, false);
  } else if (desiredHeading > _data.Heading) {
    _rightMotor.Set(255, false);
    _leftMotor.Set(255, true);
  } else {
    _rightMotor.Set(255, false);
    _leftMotor.Set(255, false);
  }
#else
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
#endif
}

void Droid::Ping() {  
  if (!_mesh->write(&_data, MSG_PING, sizeof(_data))) {
    if (!_mesh->checkConnection()) {
      _mesh->renewAddress();
    }
  }
}
