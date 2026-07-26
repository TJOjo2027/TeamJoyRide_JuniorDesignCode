#include <definitions.h>
#include <IRSensor.h>
#include <StepperMotor.h>
#include <Servo.h>
#include <LinearActuator.h>

// SENSOR OBJECT
IRSensor secondarySensor = IRSensor(IR_SENSOR_PIN); 

// LINEAR ACTUATOR OBJECTS
LinearActuator secondaryLA = LinearActuator(LINEAR_ACTUATOR_1_IN1, LINEAR_ACTUATOR_1_IN2);
LinearActuator gripperLA = LinearActuator(LINEAR_ACTUATOR_2_IN3, LINEAR_ACTUATOR_2_IN4);

// STEPPER MOTOR OBJECTS
StepperMotor primaryMotor = StepperMotor(PUL_DRIVER_PIN_1, DIR_DRIVER_PIN_1, 10, 4);
StepperMotor movingMotor = StepperMotor(PUL_DRIVER_PIN_2, DIR_DRIVER_PIN_2, 40, 1);
StepperMotor flipperMotor = StepperMotor(PUL_DRIVER_PIN_3, DIR_DRIVER_PIN_3, 20, 4);

// CLAW GRIP SERVO (OBJECT IS ALREADY MADE, NO POINT RE-INVENTING THE WHEEL)
Servo clawServo;

void setup () {
  // initialize the pins for the electronics
  secondarySensor.initPin();

  secondaryLA.initPins();
  gripperLA.initPins();

  primaryMotor.initPins();
  movingMotor.initPins();
  flipperMotor.initPins();

  clawServo.attach(CLAW_PIN, 500, 2500);
}

void loop() {
  gripperLA.retract(2);
  secondaryLA.retract(2);
}
