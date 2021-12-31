/*
    RP2040_irReceiver.h - Library for receiving NEC IR Remote Codes for Raspberry Pi R2040 controller.
    Created by CC Dharmani, on December 24, 2021.
    Released into the public domain.
*/

#include <Arduino.h>
#include "RP2040_irReceiver.h"

RP2040_irReceiver *irRxPointer;     /*declaring class pointer for handling interrupt from class function*/

/*
    Initiate the irReceiver Object, with a GPIO pin for IR input
*/
RP2040_irReceiver::RP2040_irReceiver(int pin){
    _pin = pin;
    irRxPointer = this; /*assign current instance to pointer*/
}

/*
    Initiate the irReceiver Object, with GPIO pins for IR input and feedback output (can be connected to an LED)
*/
RP2040_irReceiver::RP2040_irReceiver(int pin, int feedbackPin){
    _pin = pin;
    _feedbackPin = feedbackPin;
    feedbackEnabled = 1;
    pinMode(_feedbackPin, OUTPUT);
    irRxPointer = this; /*assign current instance to pointer*/
}

/*
    Enable the IR Receiver (this enables the GPIO interrupt on the IR Receive Pin).
*/
void RP2040_irReceiver::irRxEnable(bool enable){
    if(enable) attachInterrupt(digitalPinToInterrupt(_pin), irCallbackProxy, FALLING);
    else detachInterrupt(digitalPinToInterrupt(_pin));
}

/*
    Waits for the interrupt to receive the IR code (by polling the codeRceived flag),
    Returns when valid code is received, otherwise waits here (blocking)
*/
void RP2040_irReceiver::receiveCode(void) {
    while(!codeReceived);
    codeReceived = 0;
    return;
}

/*
    Receives IR code and prints it on serial terminal (this is a blocking function, it will not return untill a valid code is received)
*/
void RP2040_irReceiver::printCode(void) {
    char str[50];
    while(!codeReceived);
    codeReceived = 0;
    sprintf(str,"IR Code:0x%08lx, Address:0x%02x, Command:0x%02x", irCode, irAdrs, irCmd);
    Serial.println(str);
}

/*
    GPIO Interrupt Service Routine, it receives the IR code. validates it and
    raises codeReceived flag (this flag needs to be cleared manually at wherever it is being used)
*/
void RP2040_irReceiver::irCallback(void) {    
    time2 = micros();
    timeDiff = time2 - time1;
    if(start){
        if(timeDiff > 1100 && timeDiff < 1200) count++;
        else if(timeDiff > 2200 && timeDiff < 2300) { tempIrCode |= (0x80000000 >> count); count++;}
        else {start = 0; if(feedbackEnabled) digitalWrite(_feedbackPin, 0); return;}
        if(count >= 32){
            irCode = tempIrCode;
            start = 0;
            uint8_t tempAdrs = (uint8_t)(irCode >> 24);
            uint8_t tempCmd = (uint8_t)(irCode >> 8);
            irAdrs = 0;
            irCmd = 0;
            for(int i=0; i<8; i++){
                if(tempAdrs & (0x01 << i)) irAdrs |= (0x80 >> i);
                if(tempCmd  & (0x01 << i)) irCmd  |= (0x80 >> i);
            }
            tempAdrs = (uint8_t)(irCode >> 16);
            tempCmd = (uint8_t)irCode;
            irInvAdrs = 0;
            irInvCmd = 0;
            for(int i=0; i<8; i++){
                if(tempAdrs & (0x01 << i)) irInvAdrs |= (0x80 >> i);
                if(tempCmd  & (0x01 << i)) irInvCmd  |= (0x80 >> i);
            }
            
            if((irInvAdrs & irAdrs)==0 && (irInvCmd & irCmd)==0) codeReceived = 1;   /*Check validity of the code by comparing with inverse field in the code*/
            if(feedbackEnabled) digitalWrite(_feedbackPin, 0);
            return;    
        }
    }
    else{
        if(timeDiff > 13000 && timeDiff < 14000) {
            start = 1;
            count = 0;
            tempIrCode = 0;
            if(feedbackEnabled) digitalWrite(_feedbackPin, 1);
        }
    } 
    time1 = time2;
}

/*
    Proxy function to call GPIO Interrupt Service Routine, which is a class function
*/
void irCallbackProxy(void){
    irRxPointer->irCallback();
}