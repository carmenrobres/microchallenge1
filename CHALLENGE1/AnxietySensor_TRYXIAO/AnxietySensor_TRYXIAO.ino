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
      breatheMotor(200);
      delay(1000);
}


void loop() {
  unsigned long touchValue = digitalRead(D3);

  if (touchValue > threshold) { // While the person is touching the sensor this action starts

    breatheExercise ();

    delay(1000);
  
    
  } else { // Did you stop touching the touchpad and did the exercise more than 5 times?
      Serial.println("Finished breathing...");
      breatheMotor(0);
    }
  delay(10);  // Necessary
}

  

