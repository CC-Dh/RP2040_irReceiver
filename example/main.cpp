/*
    Test Code for irReceiver Library for receiving NEC IR Remote Codes.
    Created by CC Dharmani  
    Released into the public domain.
    Created: 24 Dec 2021, Last Update: 30 Jan 2022
*/
#include <Arduino.h> 
#include "irReceiver.h"

//IR Receiver Pins
//For Arduino Uno, use pin 2 or 3 (interrupt pins)
//For Pi Pico, use any digital I/O pin
const int irInputPin        = 2;
const int irFeedbackLedPin  = LED_BUILTIN;

irReceiver irRemote(irInputPin, irFeedbackLedPin); //feedback pin is optional

void setup() {
  delay(1000);
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