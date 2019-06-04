/*  Title:       Merlin Keypad Matrix
 *  Description: Read key pressed from Parker Brothers Merlin handheld game.
 *  Author:      Colin Travis
 *  Version:     0.2
 *  Modified:    11/13/2017
 *
 */
#include <Keypad.h>
#include <SPI.h>
#include "RF24.h"
#include "pitches.h"

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

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

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/
byte addresses[][6] = {"1Node","2Node"};

void setup()
{
  

  radio.begin();
  radio.openWritingPipe(addresses[0]);
}

void loop()
{
  char key = keypad.getKey();
  if(key){

//    radio.write(&key, sizeof(key));
//    tone(14,NOTE_G3,100);
//    delay(50);
//    noTone(14);
//}


//  if(key == "1"){
//
//    radio.write(&key, sizeof(key));
//    tone(14,NOTE_G3,100);
//    delay(50);
//    noTone(14);
//  }
//    if(key == "3"){
//
//    radio.write(&key, sizeof(key));
//    tone(14,NOTE_G3,100);
//    delay(50);
//    noTone(14);
//  }



    switch (key)
    {
    case '1':

      tone(14,NOTE_G3,100);
      delay(100);
      noTone(14);
      radio.powerUp();

      radio.write(&key, sizeof(key));

      radio.powerDown();

      break;
    case '2':

      tone(14,NOTE_C4,200);
      delay(100);
      noTone(14);
      radio.powerUp();
      radio.write(&key, sizeof(key));
      radio.powerDown();
      break;
    case '3':

      tone(14,NOTE_D4,100);
      delay(100);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case '4':

      tone(14,NOTE_E4,100);
      delay(100);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case '5':

      tone(14,NOTE_F4,200);
      delay(100);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case '6':

      tone(14,NOTE_G4,200);
      delay(100);
      noTone(14);
      radio.write(&key, sizeof(key));

      break;
    case '7':

      tone(14,NOTE_A4,200);
      delay(100);
      noTone(14);
      radio.write(&key, sizeof(key));

      break;
    case '8':

      tone(14,NOTE_B4,200);
      delay(100);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case '9':

      tone(14,NOTE_C5,200);
      delay(100);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case '0':

      tone(14,NOTE_D5,200);
      delay(100);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case 'A':

      tone(14,NOTE_C5,75);
      delay(75);
      tone(14,NOTE_F5,75);
      delay(75);
      tone(14,NOTE_D6,80);
      delay(80);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;

    case 'B':

      tone(14,NOTE_C5,75);
      delay(75);
      tone(14,NOTE_F5,75);
      delay(75);
      tone(14,NOTE_D6,80);
      delay(80);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case 'C':

      tone(14,NOTE_C5,75);
      delay(75);
      tone(14,NOTE_F5,75);
      delay(75);
      tone(14,NOTE_D6,80);
      delay(80);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case 'D':

      tone(14,NOTE_C5,75);
      delay(75);
      tone(14,NOTE_F5,75);
      delay(75);
      tone(14,NOTE_D6,80);
      delay(80);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    case 'E':

      tone(14,NOTE_C5,75);
      delay(75);
      tone(14,NOTE_F5,75);
      delay(75);
      tone(14,NOTE_D6,80);
      delay(80);
      noTone(14);
      radio.write(&key, sizeof(key));
      break;
    }
  }
}
