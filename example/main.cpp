
/*
    Test Code for RP2040_irReceiver Library for receiving NEC IR Remote Codes for Raspberry Pi R2040 controller.
    Created by CC Dharmani, on December 24, 2021.
    Released into the public domain.
*/

#include <Arduino.h>
#include "RP2040_irReceiver.h"

RP2040_irReceiver irRemote(p14);

void setup() {
  // put your setup code here, to run once:
  sleep_ms(1000);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("\nIR Remote Test Code:");
  irRemote.irRxEnable(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  irRemote.printCode();
}