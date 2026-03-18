//
// Created by tojo on 3/17/2026.
//

#include <Arduino.h>
#include <cstdint>

#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
    public:
        // constructor
        IRSensor(uint8_t pin);

        // getter for the pin number (used in wider scope)
        uint8_t getPinNum();

        // simplified function for initializing the pin
        void initPin();

        // checks for the object being present (for simplifying the sensor logic)
        bool isObjectPresent();
    private:

        // data member for the digital pin
        uint8_t pin;
};

IRSensor::IRSensor(uint8_t pin) {
    this -> pin = pin;
}

uint8_t IRSensor::getPinNum() {
    return pin;
}

void IRSensor::initPin() {
    pinMode(pin, INPUT);
}

bool isObjectPresent() {
    return digitalRead(pin) == LOW;
}


#endif //IRSENSOR_H
