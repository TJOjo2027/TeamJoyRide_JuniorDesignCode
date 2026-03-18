//
// Created by tojo on 3/17/2026.
//

#include <Arduino.h>

#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
    public:
        // constructor
        IRSensor(uint8_t pin) {
            this -> pin = pin;
        }

        // getter for the pin number (used in wider scope)
        uint8_t getPinNum() {
            return pin;
        }

        // simplified function for initializing the pin
        void initPin() {
            pinMode(pin, INPUT);
        }

        // checks for the object being present (for simplifying the sensor logic)
        bool isObjectPresent() {
            return digitalRead(pin) == LOW;
        }
    private:
        // data member for the digital pin
        uint8_t pin;
};
#endif //IRSENSOR_H
