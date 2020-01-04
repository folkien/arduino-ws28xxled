#include "led.h"
#include "protocol.h"
#include "version.h"


// Communication section
// ------------------------------------

// Create protocol object
static Protocol protocol;

void CommunicationInit()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
  Serial.write(VERSION);
  Serial.write(AUTHOR);
}

void CommunicationLoop()
{
  char readByte = 0;
  while (Serial.available() > 0) 
  {
    readByte = Serial.read();
    protocol.Receive(readByte);
  }
}

// ------------------------------------


void setup() {
  Led::GetInstance().Init();
  Led::GetInstance().Refresh();
  CommunicationInit();
}

void loop() {
  CommunicationLoop();
}
