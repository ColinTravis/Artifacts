/*  Title:       Speak n Spell
 *  Description: Send keyboard code over RF when keypad button is pressed on a Speak n Spell toy.
 *  Author:      Colin Travis
 *  Version:     0.2
 *  Modified:    12/1/2017
 */

#define DEBUG true
#include <SPI.h>
#include "RF24.h"
#include <LiquidCrystal.h>
#include "pitches.h"
#include <Keypad.h>

#define speakerPin 12
// Delay routine for LCD display
long previousMillis = 0;
long screenDelay = 5000;


// /////////////////////////////////////////////////////////////////////////////
// Define the Keymap for the Speak n Spell

// Keypad connector has 13 pins, map them to Mega pins
const byte ROWS = 5; // Five rows of keys
const byte COLS = 8; // Eight columns of keys
// Speak n spell rows 1 = 22, 2 = 23, 11 = 32, 12 = 33, 13 = 34
// Speak n spell cols 3 = 24, 4 = 25, 5 = 26, 6 = 27, 7 = 28, 8 = 29 , 9 = 30, 10 = 31
byte rowPins[ROWS] = { 22, 23, 32, 33, 34};
byte colPins[COLS] = { 24, 25, 26, 27, 28, 29, 30, 31};

// Map special buttons to definable keys
// OFF = @, GO = %, REPLAY = <, ??? = !, " = $, :) = (, ON = ), RETURN = *
char keys[ROWS][COLS] = {
  {'U','K','@','A','F','?','P','Z'},
  {'V','L','%','B','G','&','Q','`'},
  {'W','M','<','C','H','!','R','#'},
  {'X','N','$','D','I','(','S','/'},
  {'Y','O','_','E','J',')','T','*'}
};

// Create the Keypad object
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// /////////////////////////////////////////////////////////////////////////////
// LCD Display pins = wire color = Mega pin
// ----------------------------------------
// rs = Orange = 7
// en = Orange/white = 6
// d4 = Brown = 5
// d5 = Brown/White = 4
// d6 = Blue = 3
// d7 = Blue/White = 2
// A = Green = +5
// K = Green/White = Gnd
// RW = Blue = Gnd
// VSS = Green/White = Gnd
// VDD = Green = +5

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Strings for Screen
const String phrases[ROWS][COLS] = {
  {"Reduction","Crumble","Plummet","Entertainment","Refresh","Caring","Sizzle","Theatrics"},
  {"Purchase & Sell","Wake Up","Educate","Listen","Beautification","Wealth","Public Voice","Illuminate"},
  {"Fast & Improved","Sharing","Individualism","Luxury","Glamour","Cutting Edge","Naturalistic","Friendship"},
  {"Longevity","Trust","Exotic","Anytime","Hi Fidelity","Interconnection","Negotiations","Halt"},
  {"Tremors","Summary","Rise & Fall","Silence","Might","Listening","Smokescreen","Desolation"}
};

// /////////////////////////////////////////////////////////////////////////////
// Set up nRF24L01 radio
// Contacts from the NRF24L01 radio to mega pins
//     1 = GND                       2 = +3.3
//     3 = CE -> pin 9 on Mega       4 = CSN -> pin 53 on Mega
//     5 = SCK -> pin 52 on Mega     6 = MISO -> pin 50 on Mega
//     7 = MOSI -> pin 51 on Mega    8 = not connected

RF24 radio(9, 53);
const uint64_t pipe = 0xE8E8F0F0E1LL; // Transmitter address

// /////////////////////////////////////////////////////////////////////////////
//                               Functions                                    //
// /////////////////////////////////////////////////////////////////////////////
//  Plays a triple note ascending
void playTripleNoteAsc() {
  tone(speakerPin,NOTE_C5,75);
  delay(75);
  tone(speakerPin,NOTE_F5,75);
  delay(75);
  tone(speakerPin,NOTE_D6,80);
  delay(80);
  noTone(speakerPin);
}

//  Plays a triple note descending
void playTripleNoteDes() {
  tone(speakerPin,NOTE_D6,75);
  delay(75);
  tone(speakerPin,NOTE_F5,75);
  delay(75);
  tone(speakerPin,NOTE_C5,80);
  delay(80);
  noTone(speakerPin);
}

// Reset screen to display Waiting for button press
void resetScreen(){
//  delay(screenDelay);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Waiting for");
  lcd.setCursor(0, 1);
  lcd.write("button press...");
}

// /////////////////////////////////////////////////////////////////////////////
//                            Setup and Loop                                  //
// /////////////////////////////////////////////////////////////////////////////
void setup() {
  lcd.begin(16, 2);
  if (DEBUG) Serial.begin(9600);

  // the following statements improve transmission range
  radio.begin();
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openWritingPipe(pipe); // set the transmitter address
  if (DEBUG) Serial.println("Serial working.");

  // Initializing Radio - Delay
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Initializing...");
  for(int i=5; i >= 0; i--){
    lcd.setCursor(0,1);
    lcd.print(i);
    if (DEBUG) Serial.println(i);
    delay(1000);
  }
  resetScreen();

  // Play Initial Notes
  playTripleNoteAsc();
}

void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > screenDelay) {
    previousMillis = currentMillis;
    resetScreen();
  }
  char key = keypad.getKey();
  String ph;
  if(key){
    radio.powerUp();
    radio.write(&key, sizeof(key));
    radio.powerDown();
    if (DEBUG) Serial.println(key);
    noTone(speakerPin);
    // Look up phrase in array
    for (int i=0; i<ROWS; i++){
      for (int k=0; k<COLS; k++){
        if (key == keys[i][k]){
          ph = phrases[i][k];
          break;
        }
      }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(ph);
    previousMillis = currentMillis;
    if (DEBUG) Serial.println(" Radio sent");
    tone(speakerPin, NOTE_G3, 100);
  }
}
