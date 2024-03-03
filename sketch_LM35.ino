#include <TimerOne.h>

const int sensorPin = A0;  // LM35 sensor pin connected to Analog pin A0
const int ledPin = 13;      // Onboard LED pin

float temperature = 0;
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  Timer1.initialize(500000);  // Timer1 set to 500ms (500,000 microseconds)
  Timer1.attachInterrupt(blinkLed);  // Attach the blinkLed function to Timer1
}

void loop() {
  temperature = readTemperature();
  
  if (temperature < 30) {
    Timer1.setPeriod(250000);  // Set Timer1 period to 250ms (250,000 microseconds)
  } else {
    Timer1.setPeriod(500000);  // Set Timer1 period to 500ms (500,000 microseconds)
  }
}

float readTemperature() {
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);  // Convert sensor value to voltage
  float tempC = voltage * 100;  // LM35 outputs 10mV per degree Celsius
  return tempC;
}

void blinkLed() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}