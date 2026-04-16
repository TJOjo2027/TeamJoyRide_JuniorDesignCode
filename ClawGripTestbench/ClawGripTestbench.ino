#include <Servo.h>
#include <definitions.h>

Servo clawServo;

void setup() {
  // We start with the servo detached for safety during boot-up
}

void loop() {
  clawServo.attach(CLAW_PIN);
  clawServo.write(0);
  delay(1500); // Wait for physical movement

  clawServo.write(180);
  delay(1500);

  // This releases the motor so it stops humming/drawing power
  clawServo.detach();
  
  // Wait 5 seconds before the next cycle
  delay(5000);
}