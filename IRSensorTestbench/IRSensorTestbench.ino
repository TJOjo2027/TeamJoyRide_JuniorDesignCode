#include <IRSensor.h>
#include <definitions.h>

// using the pin number
IRSensor mySensor(IR_SENSOR_PIN); 

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
    }
    else {
      Serial.println("NO OBJECT SENSED!");
    }

    // read the values every second
    delay(1000);
}