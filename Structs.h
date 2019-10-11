#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct Point {
  double Latitude;
  double Longitude;
};

struct DroidData {
  double Latitude;
  double Longitude;
  double Heading;
  double Speed;
  double Altitude;
  unsigned char NumSatellites;
};

#endif
