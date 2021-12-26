#include <Arduino.h>
#include "RP2040_irReceiver.h"

RP2040_irReceiver irRemote(p14);

void setup() {
  // put your setup code here, to run once:
  sleep_ms(1000);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("\nIR Remote Test Code:\n");
  irRemote.irRxEnable(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  irRemote.printCode();
}

//ALternative loop() implementation:
/*
void loop() {
  // put your main code here, to run repeatedly:
  char str[50];
  while(!irRemote.codeReceived) irRemote.receiveCode();
  irRemote.codeReceived = 0;
  sprintf(str,"IR Code:0x%08lx, Address:0x%02x, Command:0x%02x", irRemote.irCode, irRemote.irAdrs, irRemote.irCmd);
  Serial.println(str);
}
*/