#include <definitions.h>
#include <IRSensor.h>
#include <StepperMotor.h>
#include <Servo.h>
#include <LinearActuator.h>

// SENSOR OBJECT
IRSensor mySensor(IR_SENSOR_PIN); 

// LINEAR ACTUATOR OBJECTS
LinearActuator LinearActuator1(LINEAR_ACTUATOR_1_IN1, LINEAR_ACTUATOR_1_IN2);
LinearActuator LinearActuator2(LINEAR_ACTUATOR_2_IN1, LINEAR_ACTUATOR_2_IN2);

// STEPPER MOTOR OBJECTS
StepperMotor Motor1 = StepperMotor(PUL_DRIVER_PIN_1, DIR_DRIVER_PIN_1, 50, 1);
StepperMotor Motor2 = StepperMotor(PUL_DRIVER_PIN_2, DIR_DRIVER_PIN_2, 50, 1);
StepperMotor Motor3 = StepperMotor(PUL_DRIVER_PIN_3, DIR_DRIVER_PIN_3, 50, 1);

// CLAW GRIP SERVO (OBJECT IS ALREADY MADE, NO POINT RE-INVENTING THE WHEEL)
Servo clawServo;

void setup () {
  // initialize the pins for the electronics
  mySensor.initPin();

  LinearActuator1.initPins();
  LinearActuator2.initPins();

  Motor1.initPins();
  Motor2.initPins();
  Motor3.initPins();

  // no init for ClawGrip because we are trying to conserve the motor
  // we will attach and detach the pin through code during run time to prevent overheating
}

void loop () {
  // SENSOR STAGE

  while (!mySensor.isObjectPresent()) {
    // infinite loop until you sense something
  }

  delay(1000);

  // LINEAR ACUATOR STAGE

  // EXTEND AND STOP
  LinearActuator1.extend(2);
  LinearActuator1.stop(2);

  LinearActuator2.extend(2);
  LinearActuator2.stop(2);
  
  // RETRACT AND STOP
  LinearActuator1.retract(2);
  LinearActuator1.stop(2);

  LinearActuator2.retract(2);
  LinearActuator2.stop(2);

  delay(1000);

  // MOTOR STAGE

  SyncRotationParam params[] = {
    SyncRotationParam(&Motor1, true, 2.0),
    SyncRotationParam(&Motor2, false, 2.0),
    SyncRotationParam(&Motor3, true, 2.0)
  };

  SynchoRotate(params, 3);

  Motor1.rotateCounterClockwise(2.0);
  Motor2.rotateClockwise(2.0);
  Motor3.rotateCounterClockwise(2.0);

  delay(1000);
  
  // CLAW GRIP STAGE

  clawServo.attach(CLAW_PIN);

  clawServo.write(CLAW_GRIP_CLOSED); // CLOSE
  delay(500);

  clawServo.write(CLAW_GRIP_OPEN); // OPEN
  delay(1500);

  clawServo.write(CLAW_GRIP_CLOSED); // CLOSE AGAIN
  delay(500);

  // This releases the motor so it stops humming/drawing power
  clawServo.detach();

  delay(1000);
}