#include <Arduino.h>

#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

class StepperMotor {
    public:
        // constructor
        StepperMotor(uint8_t pulPin, uint8_t dirPin, uint8_t RPM) {
            this -> pulPin = pulPin;
            this -> dirPin = dirPin;
            // limit RPM to 150 to prevent the motor from overheating
            if (RPM > 150) {
                this -> RPM = 150;
            }
            else {
                this -> RPM = RPM;
            }
        }

        // getters for the pin numbers (used in wider scope)
        uint8_t getPulPin() {
            return pulPin;
        }

        uint8_t getDirPin() {
            return dirPin;
        }

        uint8_t getRPM() {
            return RPM;
        }

        // setter for the RPM (in case we want to change the speed of the motor during runtime)
        void setRPM(uint8_t RPM) {
            // limit RPM to 150 to prevent the motor from overheating
            if (RPM > 150) {
                this -> RPM = 150;
            }
            else {
                this -> RPM = RPM;
            }
        }

        uint16_t getPulseDelayInMicroSeconds() {
            // calculates the delay in microseconds based on the RPM

            // the formula is derived from the fact that there are 200 steps in a full rotation of the motor
            // and we want to calculate the delay for each step based on the desired RPM

            // ignores decimals, but its fine because delay() only accepts integers
            return 150000 / RPM;
        }

        // simplified function for initializing the pins
        void initPins() {
            pinMode(pulPin, OUTPUT);
            pinMode(dirPin, OUTPUT);
        }

        // motor rotation functions (POSSIBLE SENSOR FUNCTIONALITY IN THE FUTURE)

        // parameters is the number of rotations, enabling functionality for degree-based rotation
        // ex. 0.5 rotations = 180 degrees, 1 rotation = 360 degrees, etc.

        void rotateClockwise(double rotations) {
            // sets the direction pin to HIGH for clockwise rotation
            digitalWrite(dirPin, HIGH);

            for (uint16_t i = 0; i < rotations * 200; i++) {
                digitalWrite(pulPin, HIGH);
                delayMicroseconds(getPulseDelayInMicroSeconds());
                digitalWrite(pulPin, LOW);
                delayMicroseconds(getPulseDelayInMicroSeconds());
            }
        }

        void rotateCounterClockwise(double rotations) {
            // sets the direction pin to LOW for counterclockwise rotation
            digitalWrite(dirPin, LOW);

            for (uint16_t i = 0; i < rotations * 200; i++) {
                digitalWrite(pulPin, HIGH);
                delayMicroseconds(getPulseDelayInMicroSeconds());
                digitalWrite(pulPin, LOW);
                delayMicroseconds(getPulseDelayInMicroSeconds());
            }
        }

    private:
        // data members for the digital pins and RPM
        uint8_t pulPin;
        uint8_t dirPin;
        uint8_t RPM;
};

#endif //STEPPERMOTOR_H