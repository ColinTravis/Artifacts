#include <SPI.h>
#include "RF24.h"

char senderData;

RF24 radio(7, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL; // this is the transmitter address

void setup() {
  Serial.begin(9600);
  Serial.println("Starting to Listen...");

  radio.begin();
  // the following statements improve transmission range
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openReadingPipe(1, pipe); // Open one of the 6 pipes for reception
  radio.startListening(); // begin to listen
}

void loop() {
  if (radio.available()) {
    radio.read(&senderData, sizeof(senderData));
    Serial.println(senderData);
    tone(4, 2000,200);
  }
}
