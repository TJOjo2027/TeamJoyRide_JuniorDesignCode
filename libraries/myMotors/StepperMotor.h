#include <Arduino.h>

#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

// need to add enable logic

class StepperMotor {
    public:
        // constructor
        StepperMotor(uint8_t pulPin, uint8_t dirPin, uint8_t RPM = 50, uint8_t microStepValue = 1) {
            this -> pulPin = pulPin;
            this -> dirPin = dirPin;
            // limit RPM to 150 to prevent the motor from overheating
            if (RPM > 150) {
                this -> RPM = 150;
            }
            else {
                this -> RPM = RPM;
            }
            // set the microstep value for the driver
            this -> microStepValue = microStepValue;
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

        // setter for the microstep value (in case we want to change the microstepping during runtime)
        void setMicroStepValue(uint8_t microStepValue) {
            this -> microStepValue = microStepValue;
        }

        // getter for the microstep value (used in wider scope)
        uint8_t getMicroStepValue() {
            return microStepValue;
        }

        uint32_t getPulseDelayInMicroSeconds() {
            // calculates the delay in microseconds based on the RPM

            // the formula is derived from the fact that there are 200 steps in a full rotation of the motor
            // and we want to calculate the delay for each step based on the desired RPM

            // ignores decimals, but its fine because delay() only accepts integers
            return 150000 / (RPM * microStepValue);
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

            for (int i = 0; i < static_cast<int>(rotations * microStepValue * 200); i++) {
                digitalWrite(pulPin, HIGH);
                delayMicroseconds(getPulseDelayInMicroSeconds());
                digitalWrite(pulPin, LOW);
                delayMicroseconds(getPulseDelayInMicroSeconds());
            }
        }

        void rotateCounterClockwise(double rotations) {
            // sets the direction pin to LOW for counterclockwise rotation
            digitalWrite(dirPin, LOW);

            for (int i = 0; i < static_cast<int>(rotations * microStepValue * 200); i++) {
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
        uint8_t microStepValue;
};

struct SyncRotationParam {
    StepperMotor* motor;
    bool isClockwise; // true for clockwise, false for counterclockwise
    double rotations;
    unsigned int steps; // calculated based on the rotations and microstepping, used for synchronization

    SyncRotationParam(StepperMotor* motor, bool isClockwise, double rotations) {
        this -> motor = motor;
        this -> isClockwise = isClockwise;
        this -> rotations = rotations;
        this -> steps = 0; // will be calculated later
    }
};

// goes off the assumption that all the motors have the same microstepping and RPM value, very important because this is a single core processor
// this allows for motors to rotates simultaneously without needing to use multithreading (which is not possible on an Arduino) or interrupts (which can get complicated and may not be necessary for us)
// there can be multiple combinations of rotations and directions for the motors, but the function will ensure that they all start and stop at the same time based on the motor that needs to rotate the most (in terms of steps)
void SynchoRotate(SyncRotationParam paramsArray[], size_t arraySize) {
    // determine the direction of the rotation for the motors
    // while doing that, also find the number of steps needed for each motor to complete its process
    for (int i = 0; i < arraySize; i++) {
        if (paramsArray[i].isClockwise) {
            digitalWrite(paramsArray[i].motor->getDirPin(), HIGH);
        }
        else {
            digitalWrite(paramsArray[i].motor->getDirPin(), LOW);
        }

        // calculate steps
        paramsArray[i].steps = static_cast<unsigned int>(paramsArray[i].rotations * paramsArray[i].motor->getMicroStepValue() * 200);
    }

    // find the maximum number of steps needed among the motors to determine how many iterations we need to do
    unsigned int maxSteps = 0;
    for (int i = 0; i < arraySize; i++) {
        if (paramsArray[i].steps > maxSteps) {
            maxSteps = paramsArray[i].steps;
        }
    }
    
    // now we have the maximum number of steps needed, we can iterate through that and pulse the motors accordingly
    for (unsigned int step = 0; step < maxSteps; step++) {
        for (unsigned int i = 0; i < arraySize; i++) {
            if (step < paramsArray[i].steps) {
                // pulse the motor
                digitalWrite(paramsArray[i].motor->getPulPin(), HIGH);
            }
        }

        // delay for the pulse duration
        delayMicroseconds(paramsArray[0].motor->getPulseDelayInMicroSeconds());

        for (unsigned int i = 0; i < arraySize; i++) {
            if (step < paramsArray[i].steps) {
                // end the pulse
                digitalWrite(paramsArray[i].motor->getPulPin(), LOW);
            }
        }

        // delay for the pulse duration again before the next pulse
        delayMicroseconds(paramsArray[0].motor->getPulseDelayInMicroSeconds());
    }
}

#endif //STEPPERMOTOR_H