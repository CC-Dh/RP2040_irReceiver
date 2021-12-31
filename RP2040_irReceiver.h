/*
    RP2040_irReceiver.h - Library for receiving NEC IR Remote Codes for Raspberry Pi R2040 controller.
    Created by CC Dharmani, on December 24, 2021.
    Released into the public domain.
*/
#ifndef RP2040_IRRECEIVER_H
#define RP2040_IRRECEIVER_H

#include <Arduino.h>

class RP2040_irReceiver{
    public:
        volatile uint32_t irCode;        /* this is 32 bit IR Code as received bit-by-bit on the GPIO pin */
        volatile bool codeReceived=0;    /* this flag is set when a valid code is received, must be cleared manually */
        volatile uint8_t irCmd, irInvCmd, irAdrs, irInvAdrs;  /* this variables contain decoded data from the IR code, with bits rearranged (for correct MSB-LSB order) */

        /*
            Initiate the irReceiver Object, with a GPIO pin for IR input
        */
        RP2040_irReceiver(int pin);
        /*
            Initiate the irReceiver Object, with GPIO pins for IR input and feedback output (can be connected to an LED)
        */
        RP2040_irReceiver(int pin, int feedbackPin);
        /*
            Enable the IR Receiver (this enables the GPIO interrupt on the IR Receive Pin).
        */
        void irRxEnable(bool enable);
        /*
            Waits for the interrupt to receive the IR code (by polling the codeRceived flag),
			Returns when valid code is received, otherwise waits here (blocking)
        */
        void receiveCode(void);
        /*
            Receives IR code and prints it on serial terminal (this is a blocking function, it will not return untill a valid code is received)
        */
        void printCode(void);
        /*
            GPIO Interrupt Service Routine, it receives the IR code. validates it and
			raises codeReceived flag (this flag needs to be cleared manually at wherever it is being used)
        */
        void irCallback(void);

    private:
        int _pin, _feedbackPin;
        bool feedbackEnabled = 0;
        volatile int count=0;
        volatile bool start = 0; 
        volatile uint32_t time1 = 0, time2=0, tempIrCode=0; 
        uint32_t timeDiff;
};

/*
    Proxy function to call GPIO Interrupt Service Routine, which is a class function
*/
void irCallbackProxy(void);

#endif
