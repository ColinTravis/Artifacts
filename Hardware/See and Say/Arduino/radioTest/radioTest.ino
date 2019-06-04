/*  Title:       Merlin Keypad Matrix
 *  Description: Read key pressed from Parker Brothers Merlin handheld game.
 *  Author:      Colin Travis
 *  Version:     1.0
 *  Modified:    11/19/2017
 */
#include <SPI.h>
#include "RF24.h"
#include "pitches.h"

// pin speaker is connected to
#define speakerPin 14

// notes for each key
int keyNotes[] = {NOTE_D5, NOTE_G3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};

// The Merlin keypad is one piece of clear thin flexible plastic with Metallic pads
//   printed on one side, that when folded in half will touch each other
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Hardware configuration: Set up nRF24L01 radio on SPI bus
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void playNote(char note, int delayTime){
  tone(speakerPin,keyNotes[note],delayTime);
 // Serial.println(keyNotes[note]);
  delay(delayTime);
  noTone(speakerPin);
}
void playTripleNoteAsc() {
  tone(speakerPin,NOTE_C5,75);
  delay(75);
  tone(speakerPin,NOTE_F5,75);
  delay(75);
  tone(speakerPin,NOTE_D6,80);
  delay(80);
  noTone(speakerPin);
}
void playTripleNoteDes() {
  tone(speakerPin,NOTE_D6,75);
  delay(75);
  tone(speakerPin,NOTE_F5,75);
  delay(75);
  tone(speakerPin,NOTE_C5,80);
  delay(80);
  noTone(speakerPin);
}

void setup() {
  pinMode(ledPin, OUTPUT);

 // Serial.begin(9600);
 // Serial.println("Merlin Matrix with radio");

  radio.begin();
  // the following statements improve transmission range
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openWritingPipe(pipe); // set the transmitter address

  for(int i=0; i < 10; i++){
   // Serial.println(keyNotes[i]);
    }

  // Play Initial Notes
  playTripleNoteAsc();

}

void loop() {
   // Serial.println(key);
   if(digitalRead(10) == LOW){
    radio.powerUp();
   // Serial.println("Power up");
    radio.write(&key, sizeof(key));
   // Serial.println("Radio send");
    radio.powerDown();
   // Serial.println("Radio power down");
 }

}
