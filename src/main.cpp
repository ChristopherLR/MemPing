#include <Arduino.h>

#define RED_LED 8
#define GREEN_LED 7

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  delay(1000);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  Serial.println("TEST");
  delay(1000);
}