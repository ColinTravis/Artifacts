#include <SPI.h>
#include "RF24.h"

RF24 radio(3, 4);
const uint64_t pipe = 0xE8E8F0F0E1LL;
char test;

void setup()
{
  test = 2;
//  pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openWritingPipe(pipe); // set the transmitter address
  
}

void loop()
{
    radio.write(&test, 1);
    delay(500);
}
