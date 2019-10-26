#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Component.h"
#include <RF24Mesh.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <EEPROM.h>

class Object
{
private:
  int _nodeId;

protected:
  int _radioCe = 5;
  int _radioCs = 6;

  RF24 *_radio;
  RF24Network *_network;
  RF24Mesh *_mesh;

public:
  Object(int nodeId);
  virtual void Setup();
  virtual void Update();
};

#endif
