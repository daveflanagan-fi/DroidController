#ifndef __CONFIG_H__
#define __CONFIG_H__

#define BOARD_VERSION_MAJOR 1
#define BOARD_VERSION_MINOR 2
#define BOARD_VERSION_REVISION 1

// Radio variables
#define RADIO_CE 5
#define RADIO_CS 6
#define NODE_ID 1

// Droid contro charactericstics
#define TURNING_RADIUS 30
#define TARGET_SPEED 10
#define UPDATE_INTERVAL 1000
#define CONTROL_INTERVAL 100
#define MAX_WAYPOINTS 20

// GPS settings
#define MAGNETIC_DECLINATION 0.21
#define GPS_BAUDRATE 9600
#define GPS_RX 3
#define GPS_TX 2

// Voltage divider settings
#define VD_PIN A2
#define VD_R1 47000.0
#define VD_R2 33000.0
#define BATT_MIN 10
#define BATT_MAX 12.6

// Motor pins
#define IN1 4
#define IN2 7
#define IN3 8
#define IN4 10
#define EN1 A1
#define EN2 A0

// Message types
#define MSG_ADDR 1
#define MSG_ERROR 2
#define MSG_PING 65
#define MSG_ADD_WAYPOINT 66
#define MSG_REP_WAYPOINT 67
#define MSG_COMPLETE 68
#define MSG_SEND_ALL 127

#endif
