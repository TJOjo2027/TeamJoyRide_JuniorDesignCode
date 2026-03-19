#include <IRSensor.h>

// using the pin number
IRSensor mySensor(4); 
uint8_t count = 0;

void setup() {
    Serial.begin(9600);
    
    mySensor.initPin();
    
    Serial.println("IRSensor Object Testbench");
    Serial.print("Initialized on Pin: ");
    Serial.println(mySensor.getPinNum()); // Testing your getter
}

void loop() {
    int status = digitalRead(mySensor.getPinNum());

    if (mySensor.isObjectPresent()) {
      Serial.println(F("OBJECT IS BEING SENSED!"));
      count++;
      Serial.print(F("Count: "));
      Serial.println(count);
    }
    else {
      Serial.println("NO OBJECT SENSED!");
    }

    // read the values every second
    delay(1000);
}