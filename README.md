# RP2040_irReceiver
IR Remote Control Code Receiver (NEC format only), for Raspberry Pi rp2040 microcontroller

This is a simple,  receiver only, Arduino compatible library for receiving IR codes of NEC format remote control.
It has provision for feedback output pin also, which can be connected to an LED.

The code uses the GPIO interrupt of rp2040 controller to measure the incoming pulses from IR receiver (for example, TSOP1738), tested on Pi Pico board.

Example:
<pre><code>
#include "Arduino.h"
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
