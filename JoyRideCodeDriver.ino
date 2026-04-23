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

void loop () {
  // SENSING FOR INPUT
  if (secondarySensor.isObjectPresent(6)) { 
    // check sensor for 6 seconds to see if the object is in front for more than 6 seconds
    // start the code if this is true
    // if false, loop back and check again!

    // extend the secondary linear actuator and stop

    secondaryLA.extend(0.66);
    secondaryLA.stop(0.25);

    // retract the linear actuator and stop

    secondaryLA.retract(0.7);
    secondaryLA.stop(0.25);

    // move the flipping motor 180 degrees counter-clockwise

    flipperMotor.rotateClockwise(0.52);
    delay(750);

    // will use syncho-rotate to save time and rotate flipper and any other motors that need to be reset

    // move the secondary from the fork and to the "assembly zone"
    movingMotor.rotateCounterClockwise(2.1); // might need to calculate a precise value for testing
 
    // open the claw gripper so that its ready for the primary tank

    for (int pos = CLAW_GRIP_CLOSED; pos <= CLAW_GRIP_OPEN; pos++) {
      clawServo.write(pos);
      delay(10);
    }
    
    // move the primary tank over to the gripper so it can close on it

    primaryMotor.rotateCounterClockwise(0.25);

    // close the claw gripper on the primary tank

    delay(750);

    for (int pos = CLAW_GRIP_OPEN; pos >= CLAW_GRIP_GRIPPING; pos--) {
      clawServo.write(pos);
      delay(15); 
    }

    // hold the block for 2 seconds
    delay(750);

    // move the primary platform away to make space for the LA to descend

    primaryMotor.rotateClockwise(0.25);

    // lower the linear actuator so the gripper can put the block in the secondary

    gripperLA.extend(1.1);
    gripperLA.stop(0.5);

    // let go of the block by opening the claw a little bit

    for (int pos = CLAW_GRIP_GRIPPING; pos < CLAW_GRIP_RELEASING; pos++) {
      clawServo.write(pos);
      delay(15); 
    }

    delay(750);

    // retract the linear actuator

    gripperLA.retract(2.1);
    gripperLA.stop(0.5);

    // move the moving platform to the export zone

    movingMotor.rotateCounterClockwise(1.4); // might need to calculate a precise value through testing

    // give user 2 seconds to pick up the assembled product
    delay(2000);

    // move the flipper motor back
    
    flipperMotor.rotateCounterClockwise(0.52);

    // return the moving platform to its original position

    movingMotor.rotateClockwise(3.5);

    // also close the gripper mouth in this time you are given
    clawServo.write(CLAW_GRIP_CLOSED);
  }
}