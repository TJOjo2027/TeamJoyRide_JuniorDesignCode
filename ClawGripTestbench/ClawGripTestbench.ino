#include <Servo.h>

Servo clawServo;
const int servoPin = 11;

void setup() {
  // We start with the servo detached for safety during boot-up
}

void loop() {
  // 1. START AT 0
  clawServo.attach(servoPin);
  clawServo.write(0);
  delay(1500); // Wait for physical movement

  clawServo.write(180);
  delay(1500);

  // This releases the motor so it stops humming/drawing power
  clawServo.detach();
  
  // 5. LOOP DELAY
  // Wait 5 seconds before the next cycle
  delay(5000);
}