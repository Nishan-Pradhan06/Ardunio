// smart light in arduino..

#include <Arduino.h>

const int ldrPin = A0;
const int trigPin = 13;
const int echoPin = 12;
const int light1Pin = 10;
const int light2Pin = 11;
const int threshold = 500;
int ldrStatus, duration, distance;

int ldr()
{
  ldrStatus = analogRead(ldrPin);
  return (ldrStatus);
}

int ultrasonic()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (0.0343 * duration) / 2;
  return distance;
}

void logic()
{
  if (ldrStatus > threshold)
  {
    digitalWrite(light2Pin, 0);
  }
  else if (ldrStatus < threshold && distance < 25)
  {
    digitalWrite(light2Pin, 1);
    delay(5000);
    digitalWrite(light2Pin, 0);
  }
  else if (ldrStatus < threshold && distance > 25)
  {
    digitalWrite(light2Pin, 0);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(light1Pin, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  ldr();
  ultrasonic();
  logic();
  Serial.print(ldrStatus);
  Serial.print("      ");
  Serial.println(distance);
}