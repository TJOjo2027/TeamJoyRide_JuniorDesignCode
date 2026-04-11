#include <definitions.h>
#include <StepperMotor.h>

StepperMotor Motor1 = StepperMotor(PUL_DRIVER_PIN_1, DIR_DRIVER_PIN_1, 50, 1);
StepperMotor Motor2 = StepperMotor(PUL_DRIVER_PIN_2, DIR_DRIVER_PIN_2, 50, 1);
StepperMotor Motor3 = StepperMotor(PUL_DRIVER_PIN_3, DIR_DRIVER_PIN_3, 50, 1);

void setup() {
  Motor1.initPins();
  Motor2.initPins();
  Motor3.initPins();
}

void loop() {
  // create the array of parameters
  SyncRotationParam params[] = {
    SyncRotationParam(&Motor1, true, 2.0),
    SyncRotationParam(&Motor2, false, 2.0),
    SyncRotationParam(&Motor3, true, 2.0)
  };

  SynchoRotate(params, 3);

  delay(2000);

  Motor1.rotateClockwise(0.25);
  Motor2.rotateClockwise(0.25);
  Motor3.rotateClockwise(0.25);

  delay(250);
}