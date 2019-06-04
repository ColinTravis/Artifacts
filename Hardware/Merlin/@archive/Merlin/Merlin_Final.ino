#include <Keypad.h>
#include <SPI.h>
#include "RF24.h"
const byte PIN_1 = 4; // Four rows
const byte PIN_2 = 4; // Four columns
char keys[PIN_1][PIN_2] = {
  {'F','B','D','E'},
  {'8','A','C','9'},
  {'4','6','7','5'},
  {'0','2','3','1'}
};
byte rowPins[PIN_1] = { 5, 6, 8, 9};
byte colPins[PIN_2] = { 10, 14, 15, 16};

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, PIN_1, PIN_2 );

RF24 radio(3, 4);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openWritingPipe(pipe); // set the transmitter address
  
}

void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    radio.write(key, 1);
  }
}
