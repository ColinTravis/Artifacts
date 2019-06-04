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

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 9, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/
byte addresses[][6] = {"1Node","2Node"};
// Used to control whether this node is sending or receiving
bool role = 1;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Merlin Matrix with radio"));
  radio.begin();
  radio.openWritingPipe(addresses[0]);

}

void loop()
{
  char key = keypad.getKey();
  if(key){
  Serial.println(key);
  }
//  switch (key)
//  {
//    case '9':
//      Serial.println("This is 9");
//      radio.write(&key, sizeof(key));
//      break;
//    case '3':
//      Serial.println("This is 3");
//      radio.write(&key, sizeof(key));
//      break;
//  }
}
