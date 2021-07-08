#include <Arduino.h>
#include "counter.h"

int increment(Counter* counter){
  if (counter->seconds >= 59){
    counter->minutes++;
    counter->seconds = 0;
  } else {
    counter->seconds++;
  }

  if (counter->minutes > 59){
    counter->hours++;
    counter->minutes = 0;
  }

  return 1;
}

int reset(Counter* counter){
  counter->seconds = 0;
  counter->minutes = 0;
  counter->hours = 0;
  return 1;
}

String get_seconds(Counter* counter){
  if (counter->seconds < 10){
    return String("0" + String(counter->seconds));
  }
  return String(counter->seconds);
}

String get_minutes(Counter* counter){
  if (counter->minutes < 10){
    return String("0" + String(counter->minutes));
  }
  return String(counter->minutes);
}

String get_hours(Counter* counter){
  return String(counter->hours);
}

String get_time(Counter* counter){
  return get_hours(counter) + ":" + get_minutes(counter) + ":" + get_seconds(counter);
}