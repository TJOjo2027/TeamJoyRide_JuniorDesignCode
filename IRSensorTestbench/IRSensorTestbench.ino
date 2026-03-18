#include <IRSensor.h>

// using the pin number
IRSensor mySensor(4); 

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
      Serial.println("OBJECT IS BEING SENSED!");
    }
    else {
      Serial.println("NO OBJECT SENSED!");
    }

    // read the values 4 times per second
    delay(250);
}