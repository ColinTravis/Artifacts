/*
 * Servomotor 360 degree
 *
 * Sample code to control a servo motor 360 degrees.
 */

#include <Servo.h>

int pin = 9;
int velocity = 95;

Servo servo;

#include <Servo.h>
Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(pin);
  // attaches the servo on pin 9 to the servo object
}
void loop() {
  myservo.attach(pin);
  delay(15);
  myservo.write(velocity);
  delay(1000);
  myservo.detach();
  delay(1000);
  myservo.attach(pin);
  delay(15);
  myservo.write(velocity + 25);
  delay(1000);
  myservo.detach();
  delay(1000);
}
