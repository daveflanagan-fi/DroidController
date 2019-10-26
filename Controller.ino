/*
  Copyright (c) 2019,Dave Flanagan
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Tank.h"
#include "Master.h"
#include "Config.h"

Object *obj;

void setup()
{
  Serial.begin(9600);

  if (NODE_ID == 0)
    obj = new Master();
  else
    obj = new Tank();
}

void loop()
{
  obj->Update();
}
