/*  Title:       Leonardo Receiver
 *  Description: Trigger Keyboard Events From Received RF
 *  Author:      Colin Travis
 *  Version:     0.1
 *  Modified:    12/6/2017
 */


#define DEBUG true
#include <SPI.h>
#include "RF24.h"
#include "Keyboard.h"

char senderData;

// Set up nRF24L01 radio
// Contacts from the NRF24L01 radio to leonardo pins
//     1 = GND                              2 = +3.3
//     3 = CE -> pin 9 on leo               4 = CSN -> pin 10 on leo
//     5 = SCK -> pin ICSP - SCK on leo     6 = MISO -> pin ICSP-MISO on leo
//     7 = MOSI -> pin ICSP-MOSI on leo     8 = not connected

RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL; // this is the transmitter address

void setup() {
  if (DEBUG) Serial.begin(9600);
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
    if (DEBUG) Serial.println(senderData);
    Keyboard.print(senderData);
    Serial.println("B ");
    Serial.println(senderData);
    }
  }

