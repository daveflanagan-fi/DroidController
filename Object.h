#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Component.h"
#include <RF24Mesh.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <EEPROM.h>

#include "Config.h"

class Object
{
protected:
  RF24 *_radio;
  RF24Network *_network;
  RF24Mesh *_mesh;

public:
  virtual void Setup();
  virtual void Update();
};

#endif
