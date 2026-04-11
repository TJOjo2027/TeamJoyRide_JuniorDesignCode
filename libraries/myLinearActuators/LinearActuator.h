#include <Arduino.h>

#ifndef LINEARACTUATOR_H
#define LINEARACTUATOR_H

class LinearActuator {
    public:
        // constructor
        LinearAcuator(uint8_t in1Pin, uint8_t in2Pin) {
            this -> in1Pin = in1Pin;
            this -> in2Pin = in2Pin;
        }

        void initPins() {
            pinMode(in1Pin, OUTPUT);
            pinMode(in2Pin, OUTPUT);
        }

        // make sure to extend and retract the same distance to prevent the 
        // linear acuator from getting stuck in an extended or retracted position

        // method to extend the linear acuator
        void extend(double durationInSeconds) {
            digitalWrite(in1Pin, HIGH);
            digitalWrite(in2Pin, LOW);
            delay(static_cast<unsigned long>(durationInSeconds * 1000)); // convert seconds to milliseconds
        }

        // method to retract the linear acuator
        void retract(double durationInSeconds) {
            digitalWrite(in1Pin, LOW);
            digitalWrite(in2Pin, HIGH);
            delay(static_cast<unsigned long>(durationInSeconds * 1000)); // convert seconds to milliseconds
        }

        // method to stop the linear acuator
        void stop(double durationInSeconds) {
            digitalWrite(in1Pin, LOW);
            digitalWrite(in2Pin, LOW);
            delay(static_cast<unsigned long>(durationInSeconds * 1000)); // convert seconds to milliseconds
        }

    private:
        uint8_t in1Pin;
        uint8_t in2Pin;
};

#endif //LINEARACTUATOR_H