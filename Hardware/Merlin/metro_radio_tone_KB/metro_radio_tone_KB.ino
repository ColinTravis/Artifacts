/*  Title:       Merlin Keypad Matrix
 *  Description: Read key pressed from Parker Brothers Merlin handheld game.
 *  Author:      Colin Travis
 *  Version:     0.5
 *  Modified:    11/18/2017
 */
#include <Keypad.h>
#include <SPI.h>
#include "RF24.h"
#include "pitches.h"

// pin speaker is connected to
#define speakerPin 14
// LED on keyboard to blink
#define ledPin 18

// notes for each key
int keyNotes[] = {NOTE_D5, NOTE_G3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};

// Used to track LED state
int ledState = LOW;

// will store last time LED was updated
unsigned long previousMillis = 0;

// interval at which to blink (milliseconds)
const long interval = 500;

// The Merlin keypad is one piece of clear thin flexible plastic with Metallic pads
//   printed on one side, that when folded in half will touch each other
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the Keymap
// A = 10
// B = NEW GAME
// C = SAME GAME
// D = HIT ME
// E = COMP TURN
// F = NOT USED
char keys[ROWS][COLS] = {
  {'F','B','D','E'},
  {'8','A','C','9'},
  {'4','6','7','5'},
  {'0','2','3','1'}
};
byte rowPins[ROWS] = { 2, 3, 4, 5};
byte colPins[COLS] = { 6, 9, 10, 19};

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Hardware configuration: Set up nRF24L01 radio on SPI bus
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup()
{
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Merlin Matrix with radio");

  radio.begin();
  // the following statements improve transmission range
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openWritingPipe(pipe); // set the transmitter address

  for(int i=0; i < 10; i++){
//    Serial.println(keyNotes[i]);
    }
}

void playNote(char note, int delayTime){
  tone(speakerPin,keyNotes[note],delayTime);
  Serial.println(keyNotes[note]);
  delay(delayTime);
  noTone(speakerPin);
}
void playTripleNote() {
  tone(speakerPin,NOTE_C5,75);
  delay(75);
  tone(speakerPin,NOTE_F5,75);
  delay(75);
  tone(speakerPin,NOTE_D6,80);
  delay(80);
  noTone(speakerPin);
}

void loop()
{
  char key = keypad.getKey();
  if(key){
    Serial.println(key);

    radio.powerUp();
    Serial.println("Power up");
    radio.write(&key, sizeof(key));
    Serial.println("Radio send");
    radio.powerDown();
    Serial.println("Radio power down");

    if (key >= 'A' and key <= 'E'){
	    playTripleNote();
    } else {
	    playNote(key-0x30, 100);
    Serial.println(key-0x30);
	}
  }

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }


}
