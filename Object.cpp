#include "Object.h"

void Object::Setup()
{
  if (BOARD_VERSION_MAJOR <= 1 && BOARD_VERSION_MINOR <= 1)
    Serial.println("Unsupported board version");

  _radio = new RF24(RADIO_CE, RADIO_CS);
  _network = new RF24Network(*_radio);
  _mesh = new RF24Mesh(*_radio, *_network);

  _mesh->setNodeID(NODE_ID);
  _mesh->begin();
}

void Object::Update()
{
  _mesh->update();
}
