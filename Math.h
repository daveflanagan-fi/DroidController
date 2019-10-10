#ifndef __MATH_H__
#define __MATH_H__

#define PI 3.1415926535897932384626433832795

double degreesToRadians(double degrees) {
  return degrees * PI / 180;
}

double radiansToDegrees(double radians) {
  return radians * 180.0 / PI;
}

double calculateDistance(double lat1, double lng1, double lat2, double lng2) {
  double dlon, dlat, a, c;
  double dist = 0.0;
  dlon = degreesToRadians(lng2 - lng1);
  dlat = degreesToRadians(lat2 - lat1);
  a = pow(sin(dlat / 2), 2) + cos(degreesToRadians(lat1)) * cos(degreesToRadians(lat2)) * pow(sin(dlon / 2), 2);
  c = 2 * atan2(sqrt(a), sqrt(1 - a));  
  dist = 637814000 * c;
  return dist;
}

double calculateHeading(double lat1, double lng1, double lat2, double lng2) {
  lat1 = degreesToRadians(lat1);
  lng1 = degreesToRadians(lng1);
  lat2 = degreesToRadians(lat2);
  lng2 = degreesToRadians(lng2);
  
  double bearing = atan2(sin(lng2 - lng1) * cos(lat2), (cos(lat1) * sin(lat2)) - (sin(lat1) * cos(lat2) * cos(lng2 - lng1)));
  bearing = radiansToDegrees(bearing);
  bearing = fmod(bearing + 360.0, 360);
  return bearing;
}

#endif
