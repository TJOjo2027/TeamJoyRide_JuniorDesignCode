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
        bool isObjectPresent(uint8_t threshold = 1) {
            uint8_t count = 0;
            for (uint8_t i = 0; i < threshold; i++) {
                if (digitalRead(pin) == LOW) {
                    count++;
                } else {
                    return false;
                }

                // only delay if there are more iterations to go
                if (i < threshold - 1) {
                    delay(1000);
                }
            }
            return count >= threshold;
        }


    private:
        // data member for the digital pin
        uint8_t pin;
};
#endif //IRSENSOR_H
