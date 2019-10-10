#include "Master.h"

void Master::Update() {
  Object::Update();
  
  _mesh->DHCP();

  if (_network->available()){
    RF24NetworkHeader header;
    _network->peek(header);
    
    switch(header.type){
      case 65: // Droid Ping
        DroidData data;
        _network->read(header, &data, sizeof(DroidData));
        Serial.print("{\"type\":65");
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
        Serial.println("}");
        break;
      default:
        Serial.print("{\"type\":");
        Serial.print(header.type);
        Serial.println("}");
        break;
    }
  }

  if (millis() - _lastList > 5000){
    _lastList = millis();
    Serial.print("{\"type\":1");
    for (int i = 0; i < _mesh->addrListTop; i++){
      Serial.print(",");
      Serial.print(_mesh->addrList[i].nodeID);
      Serial.print(":");
      Serial.print(_mesh->addrList[i].address);
    }
    Serial.println("}");
  }
}
