/*  Title:       Merlin Keypad Matrix
 *  Description: Read key pressed from Parker Brothers Merlin handheld game.
 *  Author:      Colin Travis
 *  Version:     0.2
 *  Modified:    11/13/2017
 *
 */
#include <Keypad.h>

// The Merlin keypad is one piece of clear thin flexible plastic with Metallic pads
//   printed on one side, that when folded in half will touch each other  
const byte PIN_1 = 4; // Four rows
const byte PIN_2 = 4; // Four columns
// Define the Keymap
char keys[PIN_1][PIN_2] = {
  {'15','COMP TURN','HIT ME','SAME GAME'},
  {'NEW GAME','10','8','7'},
  {'9','6','5','4'},
  {'3','2','1','0'}
};

byte rowPins[PIN_1] = { 7, 6, 4, 5};

byte colPins[PIN_2] = { 9, 8, 3, 2}; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, PIN_1, PIN_2 );

#define ledpin 13

void setup()
{
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin, HIGH);
  Serial.begin(9600);
}

void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case 'NEW GAME':
        digitalWrite(ledpin, LOW);
        break;
      case 'SAME GAME':
        digitalWrite(ledpin, HIGH);
        break;
      case 'HIT ME':
        digitalWrite(ledpin, LOW);
        break;
      case 'COMP TURN':
        digitalWrite(ledpin, HIGH);
        break;
      default:
        Serial.println(key);
    }
  }
}
