# irReceiver
IR Remote Control Code Receiver (NEC format only), for Arduino.
Tested on Arduino Uno and Raspberry Pi Pico (RP2040), should work on all arduino boards

This is a simple, interrupt based, receiver only, Arduino compatible library for receiving IR codes of NEC format remote control.
It has provision for feedback output pin also, which can be connected to an LED.

The code uses the GPIO interrupt of Arduino to measure the incoming pulses from IR receiver (for example, TSOP1738).

Example:
<pre><code>
#include "Arduino.h"
#include "irReceiver.h"

//IR Receiver Pins
//For Arduino Uno, use pin 2 or 3 (interrupt pins)
//For Pi Pico, use any digital I/O pin
const int irInputPin        = 2;
const int irFeedbackLedPin  = LED_BUILTIN;

irReceiver irRemote(irInputPin, irFeedbackLedPin); //feedback pin is optional

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
</code></pre>

Example output on terminal (when tested with remote):
<pre><code>
IR Code:0x00ff38c7, Address:0x00, Command:0x1c
IR Code:0x00ff30cf, Address:0x00, Command:0x0c
IR Code:0x00ff10ef, Address:0x00, Command:0x08
IR Code:0x00ff42bd, Address:0x00, Command:0x42
IR Code:0x00ff4ab5, Address:0x00, Command:0x52
IR Code:0x00ff5aa5, Address:0x00, Command:0x5a
</code></pre>
