
#include <Adafruit_NeoPixel.h>

#include <WiFi.h>
#include <PubSubClient.h>

#define PIN 38
#define NUMPIXELS 1
#define TOUCHPIN 4
#define MOTOR_PIN 2

unsigned long previousMillis = 0;
int interval = 1000; // Interval in milliseconds

const int threshold = 80000;
const int breatheDurationIn = 5000;   // Duration of the breathing in exercise in milliseconds
const int breatheDurationOut = 5000;  // Duration of the breathing out exercise in milliseconds
const int minIntensity = 30;          // Minimum intensity value
const int maxIntensity = 200;         // Minimum intensity value

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "Iaac-Wifi";
const char* password = "EnterIaac22@";
WiFiClient wifiClient;

const char* mqttBroker = "mqtt-staging.smartcitizen.me";
const char* mqttClientName = "carmen";
const char* mqttUser = "fablabbcn102";  // MQTT User Authentification
const char* mqttPass = "";              // MQTT Password Authentification
const char* publish_topic = "lab/mdef/carmen";
const char* subscribe_topic = "lab/mdef/sophie";
PubSubClient mqttClient(wifiClient);
int signalValue = 0;  // Renamed the variable to signalValue

bool LEDstate = false;

void mqttConnect() {

  while (!mqttClient.connected()) {

    Serial.print("Attempting MQTT connection...");

    if (mqttClient.connect(mqttClientName, mqttUser, mqttPass)) {

      Serial.println("connected");
      mqttClient.publish(publish_topic, mqttClientName);

      // Topic(s) subscription
      mqttClient.subscribe(subscribe_topic);

    } else {

      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
  for (int i = 0; i < length; i++) {
    incommingMessage += (char)payload[i];
  }
  Serial.println("Message arrived[" + String(topic) + "]" + incommingMessage);
  if (incommingMessage == "on") {
    pixels.setPixelColor(0, 255, 0, 0);
    pixels.show();
  } else if (incommingMessage == "off") {
    pixels.setPixelColor(0, 0, 0, 0);
    pixels.show();
  }
}

void breatheMotor(int intensity) {
  analogWrite(MOTOR_PIN, intensity);  // Set motor intensity using PWM
  //Serial.print("Motor at:");
  //Serial.println(intensity);
}

void customDelay(unsigned long milliseconds) {
  unsigned long currentMillis = millis(); // Get the current time
  
  // Store the starting time
  unsigned long startTime = currentMillis;

  // Wait until the desired time has passed
  while (currentMillis - startTime < milliseconds) {
    currentMillis = millis(); // Update the current time
    // You can add optional code here if you need to do something during the delay
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello");
  pixels.begin();
  pinMode(MOTOR_PIN, OUTPUT);

  // Connect to wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // MQTT setup
  mqttClient.setServer(mqttBroker, 1883);
  mqttClient.setCallback(callback);
}


void breatheExercise() {
  // Breathing in phase
  //Serial.println("Breathing in phase");
  unsigned long startTimeIn = millis();
  while (millis() - startTimeIn < breatheDurationIn) {
    int intensityIn = map(millis() - startTimeIn, 0, breatheDurationIn, minIntensity, maxIntensity);
    breatheMotor(intensityIn);
    customDelay(20);
  }

  // Signal middle
  breatheMotor(0);
  customDelay(3000);

  // Breathing out phase
  //Serial.println("Breathing out phase");
  unsigned long startTimeOut = millis();
  while (millis() - startTimeOut < breatheDurationOut) {
    int intensityOut = map(millis() - startTimeOut, 0, breatheDurationOut, maxIntensity, minIntensity);
    breatheMotor(intensityOut);
    customDelay(20);
  }
  customDelay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Check if we are still connected to the MQTT broker
  if (!mqttClient.connected()) {
    mqttConnect();
  }

  // Let PubSubClient library do his magic
  mqttClient.loop();

  unsigned long touchValue = touchRead(TOUCHPIN);

  /// REMOVE THIS
  
  if(touchValue > threshold){
    if(!LEDstate){
      mqttClient.publish(publish_topic, "on");
      LEDstate = true;
    }
  } else {
    if(LEDstate){
      mqttClient.publish(publish_topic, "off");
      LEDstate = false;
    }
  }

  ////


  Serial.println(LEDstate);
  if (touchValue > threshold) {  // While the person is touching the sensor this action starts
    Serial.println("touch");
    //if(!LEDstate){
      //mqttClient.publish(publish_topic, "on");
      //LEDstate = true;
    //}
    if (signalValue == 0) {  // Is it the first time you touch the sensor?
      // Signal Start
      breatheMotor(maxIntensity);
      customDelay(500);
      breatheMotor(0);
      customDelay(500);
      breatheMotor(maxIntensity);
      customDelay(500);
      breatheMotor(0);
      customDelay(500);
      Serial.println("active");
    }

    breatheExercise();

    customDelay(1000);
    signalValue = signalValue + 1;  // I did the breathing exercise +1

  } else if ((signalValue < 5) && (signalValue != 0) && (touchValue < threshold)) {  // Did you stop touching the touchpad but you only did the exercise less than 5 times?
    breatheExercise();
    signalValue = signalValue + 1;  // I did the breathing exercise +1

  } else {  // Did you stop touching the touchpad and did the exercise more than 5 times?
            // Serial.println("Finished breathing...");
    breatheMotor(0);
    signalValue = 0;  // reset
    //if(LEDstate){
      //mqttClient.publish(publish_topic, "off");
      //LEDstate = false;
    //}
  }
  delay(10);  // Necessary
}
