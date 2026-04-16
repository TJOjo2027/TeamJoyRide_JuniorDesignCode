#include <definitions.h>
#include <LinearActuator.h>

LinearActuator LinearActuator1(LINEAR_ACTUATOR_1_IN1, LINEAR_ACTUATOR_1_IN2);
LinearActuator LinearActuator2(LINEAR_ACTUATOR_2_IN1, LINEAR_ACTUATOR_2_IN2);

const int EXTEND_RETRACT_TIME = 1;

void setup() {
  LinearActuator1.initPins();
  LinearActuator2.initPins();
}

void loop() {
  // EXTEND AND STOP
  LinearActuator1.extend(EXTEND_RETRACT_TIME);
  LinearActuator1.stop(2);

  LinearActuator2.extend(EXTEND_RETRACT_TIME);
  LinearActuator2.stop(2);
  
  // RETRACT AND STOP
  LinearActuator1.retract(EXTEND_RETRACT_TIME);
  LinearActuator1.stop(2);

  LinearActuator2.retract(EXTEND_RETRACT_TIME);
  LinearActuator2.stop(2);

  // WAIT 5 SECONDS
  delay(5000);
}