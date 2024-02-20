
#include <Adafruit_NeoPixel.h>

#include <WiFi.h>
#include <PubSubClient.h>

#define PIN 33
#define NUMPIXELS 1
#define TOUCHPIN 4 
#define MOTOR_PIN 2

unsigned long previousMillis = 0;
int interval = 1000;  // Interval in milliseconds

const int threshold = 80000;
const int breatheDurationIn = 5000;   // Duration of the breathing in exercise in milliseconds
const int pauseDurationIn = 3000;     // Duration of the breathing in exercise in milliseconds
const int breatheDurationOut = 5000;  // Duration of the breathing out exercise in milliseconds
const int pauseDurationOut = 1000;    // Duration of the breathing in exercise in milliseconds
const int minIntensity = 30;          // Minimum intensity value
const int maxIntensity = 200;         // Minimum intensity value


unsigned long startTimeIn = 0;
int timer = breatheDurationIn + pauseDurationIn + breatheDurationOut + pauseDurationOut;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "Iaac-Wifi";
const char* password = "EnterIaac22@";
WiFiClient wifiClient;

const char* mqttBroker = "mqtt-staging.smartcitizen.me";
const char* mqttClientName = "sophie";
const char* mqttUser = "fablabbcn102";  // MQTT User Authentification
const char* mqttPass = "";              // MQTT Password Authentification
const char* publish_topic = "lab/mdef/sophie";
const char* subscribe_topic = "lab/mdef/carmen";
PubSubClient mqttClient(wifiClient);
int signalValue = 0;  // Renamed the variable to signalValue

bool LEDstate = false;

bool BREATHEstate = false;

bool TOUCHstate = false;

int motorSpeed;

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

  if (timer >= breatheDurationIn + pauseDurationIn + breatheDurationOut + pauseDurationOut) {
    startTimeIn = millis();
    timer = 0;
    Serial.println("reset");
    signalValue++;
  }

  // change to 5 times
  if (signalValue > 2 && TOUCHstate == false) {
    BREATHEstate = false;
    signalValue = 0;
    Serial.println("BREATHE STOP");
  }

  if (timer > breatheDurationIn + pauseDurationIn + breatheDurationOut) {
    breatheMotor(0);
    Serial.println("pause");
  } else if (timer > breatheDurationIn + pauseDurationIn) {
    Serial.println("breath out");
    breatheMotor(200);
  } else if (timer > breatheDurationIn) {
    Serial.println("pause");
    breatheMotor(0);
  } else if (timer > 0) {
    Serial.println("breath in");
    motorSpeed = map(timer,0,breatheDurationIn,minIntensity, maxIntensity);
    breatheMotor(motorSpeed);
  }

  timer = millis() - startTimeIn;
  /*
  if (millis() - startTimeIn < breatheDurationIn) {
    int intensityIn = map(millis() - startTimeIn, 0, breatheDurationIn, minIntensity, maxIntensity);
    breatheMotor(intensityIn);
    Serial.println("breath in");
    //delay(20);
  }

  // Signal middle
  unsigned long pauseTimeIn = millis();
  while (millis() - pauseTimeIn < 3000) {
    Serial.println("pause");
    breatheMotor(0);
  }

  // Breathing out phase
  //Serial.println("Breathing out phase");
  unsigned long startTimeOut = millis();
  while (millis() - startTimeOut < breatheDurationOut) {
    int intensityOut = map(millis() - startTimeOut, 0, breatheDurationOut, maxIntensity, minIntensity);
    breatheMotor(intensityOut);
    Serial.println("breath out");
    //delay(20);
  }

    // Signal middle
    unsigned long secondPauseTimeIn = millis();
  while (millis() - secondPauseTimeIn < 1000) {
    breatheMotor(0);
    Serial.println("pause");
  }

  signalValue++;

  // change to 5 times
  if(signalValue >= 2 && TOUCHstate == false) {
    BREATHEstate = false;
    signalValue = 0;
    Serial.println("BREATHE STOP");
  }
  */
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

  if (touchValue > threshold) {  // While the person is touching the sensor this action starts
    Serial.println("touch");
    if (!BREATHEstate) {
      BREATHEstate = true;
    }
    TOUCHstate = true;
  } else {
    TOUCHstate = false;
  }

  if (BREATHEstate) {
    if (!LEDstate) {
      mqttClient.publish(publish_topic, "on");
      LEDstate = true;
    }
    breatheExercise();
  } else {
    if (LEDstate) {
      mqttClient.publish(publish_topic, "off");
      LEDstate = false;
    }
  }
}
