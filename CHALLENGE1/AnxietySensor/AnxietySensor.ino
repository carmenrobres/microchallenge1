#define MOTOR_PIN D1
#include <Arduino.h>
#include "esp32-hal-touch.h"

const int threshold = 80000;
const int breatheDurationIn = 5500;    // Duration of the breathing in exercise in milliseconds
const int breatheDurationOut = 5000;   // Duration of the breathing out exercise in milliseconds
const int minIntensity = 30;            // Minimum intensity value
const int maxIntensity = 200;            // Minimum intensity value
int signalValue = 0; // Process

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_PIN, OUTPUT); // Set the motor pin as an output
}

void breatheMotor(int intensity) {
  analogWrite(MOTOR_PIN, intensity); // Set motor intensity using PWM
  Serial.print("Motor at:");
  Serial.println(intensity);
}

void breatheExercise () {
     // Breathing in phase
      Serial.println("Breathing in phase");
      unsigned long startTimeIn = millis();
      while (millis() - startTimeIn < breatheDurationIn) {
        int intensityIn = map(millis() - startTimeIn, 0, breatheDurationIn, minIntensity, maxIntensity);
        breatheMotor(intensityIn);
        delay(20);
      }

      // Signal middle
      breatheMotor(0);
      delay(3000);

      // Breathing out phase
      Serial.println("Breathing out phase");
      unsigned long startTimeOut = millis();
      while (millis() - startTimeOut < breatheDurationOut) {
        int intensityOut = map(millis() - startTimeOut, 0, breatheDurationOut, maxIntensity, minIntensity);
        breatheMotor(intensityOut);
        delay(20);
      }
      delay(1000);
}


void loop() {
  unsigned long touchValue = digitalRead(D3);

  if (touchValue > threshold) { // While the person is touching the sensor this action starts
    if (signalValue == 0){ // Is it the first time you touch the sensor? 
      // Signal Start
      breatheMotor(maxIntensity);
       delay(500);
      breatheMotor(0);
       delay(500);
      breatheMotor(maxIntensity);
       delay(500);
      breatheMotor(0);
       delay(500);
    }

    breatheExercise ();

    delay(1000);
    signalValue = signalValue+1; // I did the breathing exercise +1 
    
  } else if ((signalValue<5)&&(signalValue!=0)&&(touchValue < threshold)) { // Did you stop touching the touchpad but you only did the exercise less than 5 times?
      breatheExercise ();
      signalValue = signalValue+1; // I did the breathing exercise +1 
    
  } else { // Did you stop touching the touchpad and did the exercise more than 5 times?
      Serial.println("Finished breathing...");
      breatheMotor(0);
      signalValue = 0; // reset
    }
  delay(10);  // Necessary
}

  

