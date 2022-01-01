/*
    Test Code for RP2040_irReceiver Library for receiving NEC IR Remote Codes for Raspberry Pi R2040 controller.
    Created by CC Dharmani  
    Released into the public domain.
    Created: 24 Dec 2021, Last Updated: 31 Dec 2021
*/

#include "RP2040_irReceiver.h"

//IR Receiver Pins
const int irInputPin        = 14;
const int irFeedbackLedPin  = LED1;

RP2040_irReceiver irRemote(irInputPin, irFeedbackLedPin); //feedback pin is optional

void setup() {
  sleep_ms(1000);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("\nIR Remote Test Code:\n");
  irRemote.irRxEnable(true);
}

void loop() {
  //#1: the following will receive and print the code on serial terminal (blocking function)  
  irRemote.printCode(); 
  

  //#2: OR following lines can be used 
  /*
  irRemote.receiveCode();     //this is also blocking function
  char str[50];
  sprintf(str,"IR Code:0x%08lx, Address:0x%02x, Command:0x%02x", irRemote.irCode, irRemote.irAdrs, irRemote.irCmd);
  Serial.println(str);
  */

  //#3: OR following lines can be used for non blocking requirement
  /*
  if(irRemote.codeReceived){
    char str[50];
    sprintf(str,"IR Code:0x%08lx, Address:0x%02x, Command:0x%02x", irRemote.irCode, irRemote.irAdrs, irRemote.irCmd);
    Serial.println(str);
    irRemote.codeReceived = 0;
  }
  */
}