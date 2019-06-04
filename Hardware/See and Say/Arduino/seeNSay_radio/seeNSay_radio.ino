/*  Title:       See n Say
 *  Description: Send code over RF when handle is drawn on the See 'n Say toy.
 *  Author:      Colin Travis
 *  Version:     0.2
 *  Modified:    12/1/2017
 */

#define DEBUG true
#include <SPI.h>
#include "RF24.h"
#include <Bounce2.h>
#include <Servo.h>

#define SERVO_PIN 9
#define VELOCITY 150
#define SPINDELAY 1600

// /////////////////////////////////////////////////////////////////////////////
Servo seeSpeakServo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
long randNumber;

// /////////////////////////////////////////////////////////////////////////////
// Set up nRF24L01 radio
// Contacts from the NRF24L01 radio to mega mini pins
//     1 = GND                            2 = +3.3
//     3 = CE -> pin 3 on Metro mini       4 = CSN -> pin 8 on Metro mini
//     5 = SCK -> pin 13 on Metro mini     6 = MISO -> pin 12 on Metro mini
//     7 = MOSI -> pin 11 on Metro mini    8 = not connected

RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL; // Transmitter address

#define switchPin 10    // the pin number of the handle switch

const char sendCode = '~';   // This is the code sent when the switch is activated

Bounce debouncer = Bounce(); // Instantiate a Bounce object

// /////////////////////////////////////////////////////////////////////////////
//                            Setup and Loop                                  //
// /////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  // random analog noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

  // After setting up the button, setup the Bounce instance :
  debouncer.attach(switchPin);
  debouncer.interval(5); // interval in ms

  if (DEBUG) Serial.begin(9600);
  if (DEBUG) Serial.println("See n Say with radio");

  // the following statements improve transmission range
  radio.begin();
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openWritingPipe(pipe); // set the transmitter address
  if (DEBUG) Serial.println("Serial working.");
}

void loop() {
  // Update the Bounce instance :
  debouncer.update();

  // read the state of the switch into a local variable:
//  int switchValue = debouncer.read();
  int switchValue = digitalRead(10);
  if (switchValue == LOW) {
    radio.powerUp();
    if (DEBUG) Serial.println("Power up");
    radio.write(&sendCode, sizeof(sendCode));
    if (DEBUG) Serial.println("Radio send");
    radio.powerDown();
    if (DEBUG) Serial.println("Radio power down");

    // generate a random number from 2 to 4
    randNumber = random(2, 5);
    if (DEBUG) Serial.println(randNumber);

    for (int fullLoops=0; fullLoops < randNumber; fullLoops++){
      seeSpeakServo.attach(SERVO_PIN);
      seeSpeakServo.write(VELOCITY);
      if (DEBUG) Serial.println("Spinning");
      delay(SPINDELAY);
    }
    seeSpeakServo.detach();
    if (DEBUG) Serial.println("Done Spinning");
  }
}
