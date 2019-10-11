#include "Master.h"

void Master::Update() {
  Object::Update();
  
  _mesh->DHCP();

  if (Serial.available() > 0) {
    uint16_t cmd = (uint16_t)Serial.parseInt(SKIP_ALL);
    uint16_t node = (uint16_t)Serial.parseInt();
    switch (cmd) {
      case MSG_ADD_WAYPOINT:
      case MSG_REP_WAYPOINT:
      {
        Point p;
        p.Latitude = Serial.parseFloat();
        p.Longitude = Serial.parseFloat();
        if (!_mesh->write(node, &p, cmd, sizeof(Point))) {
          Serial.print("{\"type\":");
          Serial.print(MSG_ERROR);
          Serial.println(",\"error\":\"write failed\"}");
          if (!_mesh->checkConnection()) {
            Serial.print("{\"type\":");
            Serial.print(MSG_ERROR);
            Serial.println(",\"error\":\"renewing address\"}");
            _mesh->renewAddress();
          } else {
            Serial.print("{\"type\":");
            Serial.print(MSG_ERROR);
            Serial.println(",\"error\":\"test okay\"}");            
          }
        }
        break;
      }
      case MSG_SEND_ALL:
      {
        Point p;
        p.Latitude = Serial.parseFloat();
        p.Longitude = Serial.parseFloat();
        _mesh->write(&p, MSG_REP_WAYPOINT, sizeof(Point));
        break;
      }
    }
  }

  if (_network->available()){
    RF24NetworkHeader header;
    _network->peek(header);
    
    switch(header.type){
      case MSG_PING:
        DroidData data;
        _network->read(header, &data, sizeof(DroidData));
        Serial.print("{\"type\":");
        Serial.print(MSG_PING);
        Serial.print(",\"id\":");
        Serial.print(header.from_node);
        Serial.print(",\"latitude\":");
        Serial.print(data.Latitude);
        Serial.print(",\"longitude\":");
        Serial.print(data.Longitude);
        Serial.print(",\"heading\":");
        Serial.print(data.Heading);
        Serial.print(",\"speed\":");
        Serial.print(data.Speed);
        Serial.print(",\"altitude\":");
        Serial.print(data.Altitude);
        Serial.print(",\"numSatellites\":");
        Serial.print(data.NumSatellites);
        Serial.print(",\"accuracy\":");
        Serial.print(data.Accuracy);
        Serial.println("}");
        break;
      default:
        Serial.print("{\"type\":");
        Serial.print(header.type);
        Serial.print(",\"id\":");
        Serial.print(header.from_node);
        Serial.println("}");
        break;
    }
  }

  if (millis() - _lastList > 5000){
    _lastList = millis();
    Serial.print("{\"type\":");
    Serial.print(MSG_ADDR);
    for (int i = 0; i < _mesh->addrListTop; i++){
      Serial.print(",");
      Serial.print(_mesh->addrList[i].nodeID);
      Serial.print(":");
      Serial.print(_mesh->addrList[i].address);
    }
    Serial.println("}");
  }
}
