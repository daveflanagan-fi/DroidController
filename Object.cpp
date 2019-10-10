#include "Object.h"
#include "Config.h"

void Object::Setup() {
  _radio = new RF24(RADIO_CE, RADIO_CS);
  _network = new RF24Network(*_radio);
  _mesh = new RF24Mesh(*_radio, *_network);
  
  _mesh->setNodeID(NODE_ID);
  _mesh->begin();
}

void Object::Update() {
  _mesh->update();
}
