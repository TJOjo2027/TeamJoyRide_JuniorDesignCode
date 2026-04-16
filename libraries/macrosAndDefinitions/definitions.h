//
// Created by tojo on 2/20/2026.
//

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// LINEAR ACTUATOR PINS
const uint8_t LINEAR_ACTUATOR_1_IN1 = 52;
const uint8_t LINEAR_ACTUATOR_1_IN2 = 53;
const uint8_t LINEAR_ACTUATOR_2_IN1 = 54;
const uint8_t LINEAR_ACTUATOR_2_IN2 = 55;

// CLAW PINS
const uint8_t CLAW_PIN = 10;

// SENSOR PINS
const uint8_t IR_SENSOR_PIN = 40;

// STEPPER DRIVER PINS
const uint8_t PUL_DRIVER_PIN_1 = 22;
const uint8_t DIR_DRIVER_PIN_1 = 23;
const uint8_t PUL_DRIVER_PIN_2 = 24;
const uint8_t DIR_DRIVER_PIN_2 = 25;
const uint8_t PUL_DRIVER_PIN_3 = 26;
const uint8_t DIR_DRIVER_PIN_3 = 27;

// STEPPER MOTOR RPMS
const uint8_t STEPPER_MOTOR_RPM_1;
const uint8_t STEPPER_MOTOR_RPM_2;
const uint8_t STEPPER_MOTOR_RPM_3;

// CLAW GRIP DISTANCES
const uint16_t CLAW_GRIP_OPEN = 180;
const uint16_t CLAW_GRIP_CLOSED = 0;


#endif //DEFINITIONS_H
