# RP2040_irReceiver
IR Remote Control Code Receiver (MEC format only), for Raspberry Pi r2040 microcontroller

This is a simple,  receiver only, Arduino compatible library for receiving IR codes of NEC format remote control.
It has provision for feedback output pin also, which can be connected to an LED.

The code uses the GPIO interrupt of rp2040 controller to measure the incoming pulses from IR receiver (for example, TSOP1738), tested on Pi Pico board.
