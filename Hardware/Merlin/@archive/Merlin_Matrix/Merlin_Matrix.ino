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
// A = 10
// B = NEW GAME
// C = SAME GAME
// D = HIT ME
// E = COMP TURN
// F = NOT USED
char keys[PIN_1][PIN_2] = {
  {'F','E','D','B'},
  {'8','9','C','A'},
  {'4','5','7','6'},
  {'0','1','3','2'}
};

byte rowPins[PIN_1] = { 2, 3, 4, 5};
byte colPins[PIN_2] = { 6, 9, 10, 19};

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, PIN_1, PIN_2 );

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial on");
}

void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
   Serial.println(key); 
   }
}
