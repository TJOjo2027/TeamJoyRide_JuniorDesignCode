#include <definitions.h>

// change the PUL_DRIVER_PIN & DIR_DRIVER_PIN number as needed
const uint8_t ACTIVE_PUL = PUL_DRIVER_PIN_1; 
const uint8_t ACTIVE_DIR = DIR_DRIVER_PIN_1; 

void setup() {
  pinMode(PUL_DRIVER_PIN_1, OUTPUT);
  pinMode(DIR_DRIVER_PIN_1, OUTPUT);
  
  Serial.begin(9600);
  Serial.print("Testing Driver on PUL: ");
  Serial.print(ACTIVE_PUL);
  Serial.print(" | DIR: ");
  Serial.println(ACTIVE_DIR);
}

void loop() {
  // 1. Set Direction (HIGH)
  digitalWrite(ACTIVE_DIR, HIGH); // sets polarity
  Serial.println("Direction: HIGH | Rotating...");
  
  for(int i = 0; i < 200; i++) {
    digitalWrite(ACTIVE_PUL, HIGH);
    delayMicroseconds(1000);
    digitalWrite(ACTIVE_PUL, LOW);
    delayMicroseconds(1000);
  }
  
  delay(1000);

  // 2. Set Direction (LOW)
  digitalWrite(ACTIVE_DIR, LOW); // sets polarity
  Serial.println("Direction: LOW | Rotating...");
  
  for(int i = 0; i < 200; i++) {
    digitalWrite(ACTIVE_PUL, HIGH);
    delayMicroseconds(1000);
    digitalWrite(ACTIVE_PUL, LOW);
    delayMicroseconds(1000);
  }

  delay(1000);
}