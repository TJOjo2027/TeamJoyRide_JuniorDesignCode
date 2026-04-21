#include <definitions.h>
#include <StepperMotor.h>

StepperMotor Motor1 = StepperMotor(PUL_DRIVER_PIN_1, DIR_DRIVER_PIN_1, 50, 1);
StepperMotor Motor2 = StepperMotor(PUL_DRIVER_PIN_2, DIR_DRIVER_PIN_2, 25, 1);
StepperMotor Motor3 = StepperMotor(PUL_DRIVER_PIN_3, DIR_DRIVER_PIN_3, 15, 4);

void setup() {
  Motor1.initPins();
  Motor2.initPins();
  Motor3.initPins();
}

void loop() {


  Motor1.rotateCounterClockwise(0.25);

  delay(1000);

  Motor1.rotateClockwise(0.25);

  delay(1000);
}