#ifndef __STRUCTS_H__
#define __STRUCTS_H__

// Message types
#define MSG_ADDR 1
#define MSG_ERROR 2
#define MSG_PING 65
#define MSG_ADD_WAYPOINT 66
#define MSG_REP_WAYPOINT 67
#define MSG_COMPLETE 68
#define MSG_SEND_ALL 127

struct Point
{
  double Latitude;
  double Longitude;
};

struct DroidData
{
  unsigned char Battery;
  double Distance;
  double Latitude;
  double Longitude;
  double Heading;
  double Speed;
  double Altitude;
  unsigned char NumSatellites;
  unsigned short Accuracy;
};

enum Side
{
  LEFT,
  RIGHT
};

#endif
