#pragma once

typedef struct {
  unsigned char seconds;
  unsigned char minutes;
  unsigned int hours;
} Counter;

int increment(Counter* counter);
int reset(Counter* counter);
String get_seconds(Counter* counter);
String get_minutes(Counter* counter);
String get_hours(Counter* counter);
String get_time(Counter* counter);