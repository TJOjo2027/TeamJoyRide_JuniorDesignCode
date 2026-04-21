#include <Servo.h>
#include <definitions.h>

Servo clawServo;

void setup() {}

void loop() {

  // attach the pin when need to save energy
  clawServo.attach(CLAW_PIN); 

  for (int pos = CLAW_GRIP_CLOSED; pos <= CLAW_GRIP_OPEN; pos++) {
    clawServo.write(pos);
    delay(15); // Slows down the "jolt"
  }
  delay(2000); // Stay open for 2 seconds

  for (int pos = CLAW_GRIP_OPEN; pos >= CLAW_GRIP_GRIPPING; pos--) {
    clawServo.write(pos);
    delay(15); 
  }

  // hold the block for 5 seconds
  delay(5000);

  for (int pos = CLAW_GRIP_GRIPPING; pos < CLAW_GRIP_RELEASING; pos++) {
      clawServo.write(pos);
      delay(15); 
  }

  delay(5000);

  for (int pos = CLAW_GRIP_RELEASING; pos >= CLAW_GRIP_CLOSED; pos--) {
      clawServo.write(pos);
      delay(15); 
  }

  delay(5000);

  clawServo.detach();

  // Long wait so it doesn't jump back to the start of the loop immediately
  delay(5000); 
}