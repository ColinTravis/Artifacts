#include <SPI.h>
#include "RF24.h"

int senderData;

// Set up nRF24L01 radio on SPI bus plus pins 7 & 8
//Contacts from the radio to connect NRF24L01 pinamnam -> Arduino
//SCK -> 13
//MISO -> 12
//MOSI -> 11
//CSN -> 8
//CE -> 7
RF24 radio(7, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL; // this is the transmitter address

void setup() {
  Serial.begin(9600);

  radio.begin();
  // the following statements improve transmission range
  radio.setPayloadSize(1); // setting the payload size to the needed value
  radio.setDataRate(RF24_250KBPS); // reducing bandwidth
  radio.openReadingPipe(1, pipe); // Open one of the 6 pipes for reception
  radio.startListening(); // begin to listen
}

void loop() {
  if (radio.available()) {
    // read and write expect a reference to the payload (& symbol)
    // second argument is the packet length in bytes (sizeof(char) == 1)
    radio.read(&senderData, 1);
    Serial.println(senderData);
  }
}
