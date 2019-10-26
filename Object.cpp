#include "Object.h"

#define BOARD_VERSION_MAJOR 1
#define BOARD_VERSION_MINOR 2
#define BOARD_VERSION_REVISION 1

Object::Object(int nodeId)
{
  _nodeId = nodeId;
  Setup();
}

void Object::Setup()
{
  if (BOARD_VERSION_MAJOR <= 1 && BOARD_VERSION_MINOR <= 1)
    Serial.println("Unsupported board version");

  _radio = new RF24(_radioCe, _radioCs);
  _network = new RF24Network(*_radio);
  _mesh = new RF24Mesh(*_radio, *_network);

  _mesh->setNodeID(_nodeId);
  _mesh->begin();
}

void Object::Update()
{
  _mesh->update();
}
