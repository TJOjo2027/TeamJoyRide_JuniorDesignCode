#include <definitions.h>
#include <LinearActuator.h>

LinearActuator LinearActuator1(LINEAR_ACTUATOR_1_IN1, LINEAR_ACTUATOR_1_IN2);
LinearActuator LinearActuator2(LINEAR_ACTUATOR_2_IN3, LINEAR_ACTUATOR_2_IN4);

const int EXTEND_RETRACT_TIME = 2;

void setup() {
  LinearActuator1.initPins();
  LinearActuator2.initPins();
}

void loop() {
  // EXTEND AT FULL SPEED
  LinearActuator1.extend(EXTEND_RETRACT_TIME);
  LinearActuator1.stop(5);

  LinearActuator2.extend(EXTEND_RETRACT_TIME);
  LinearActuator2.stop(5);

  // RETRACT AT FULL SPEED
  LinearActuator1.retract(EXTEND_RETRACT_TIME);
  LinearActuator1.stop(5);

  LinearActuator2.retract(EXTEND_RETRACT_TIME);
  LinearActuator2.stop(5);

  // WAIT 5 SECONDS
  delay(5000);
}