//libraries
#include "FastLED.h"
#include <Servo.h> 
//LED params
#define DATA_PIN    7
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    10
#define BRIGHTNESS  50    
CRGB leds[NUM_LEDS];

const int enable = 2;  
const int out_1 = 3;
const int out_2 = 4; 
const int out_3 = 5;
const int out_4 = 6;
const int servoPin = 7; 
const int buzzer = 11;
const int ir_sense = A7;
const int trigPin = 10;
const int echoPin = 9;
long duration;
int distance;
int analog_input = A0; 
Servo Servo1;
int value;
int count = 0;
float volt;

void setup() {
  //led setup
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  //pins
  pinMode(out_1, OUTPUT);
  pinMode(out_2, OUTPUT);
  pinMode(out_3, OUTPUT);
  pinMode(out_4, OUTPUT);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ir_sense, INPUT); 
  pinMode(analog_input, INPUT);

  Serial.begin(9600);
  Servo1.attach(servoPin);
}

void loop() {
  green();
  volt = voltage(analogRead(analog_input));
  if (volt <= 4.2)low_voltage();
  distance = ultrasonic();
  //Serial.println(distance);
  if ((distance <= 30)&&(distance !=0))detected();
  else if (distance >= 31) left();
}

//light modes: 
void flash(){
  fill_solid( leds, NUM_LEDS, CRGB(255,255,255));
  FastLED.show();
  delay(20);
  fill_solid( leds, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(20);
}

void red(){
  fill_solid( leds, NUM_LEDS, CRGB(255,0,0));
  FastLED.show();
}

void orange(){
  fill_solid( leds, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
}

void green(){
  fill_solid( leds, NUM_LEDS, CRGB(0,255,0));
  FastLED.show();
}

void low_voltage(){
  orange();
  tone(buzzer, 4000, 500);
  delay(500);
  noTone(buzzer);
  red();
  delay(2000);
}

float voltage(int sensorValue){
  //int sensorValue = analogRead(analog_input);
  float voltage = sensorValue * (4.8/1023.0);
  Serial.println(sensorValue);
  Serial.print("Voltage = ");
  Serial.println(voltage);
  return voltage;
}

int ultrasonic(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds (2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  delayMicroseconds (2);
  return distance;
}

void detected(){
  Stop();
  red();
  tone(11, 1000, 1000);
  delay(1000);
  distance = ultrasonic(); 
  if (distance <= 40){
     flash();
     red(); 
     ahead();
     delay(1600);
     orange();
     back();
     delay(1600);
  }
  return;
}

void Stop(){
  digitalWrite(out_1, LOW);
  digitalWrite(out_2, LOW); 
  digitalWrite(out_3, LOW);
  digitalWrite(out_4,LOW);
}
void ahead(){
  digitalWrite(out_1, HIGH);
  digitalWrite(out_2, LOW); 
  digitalWrite(out_3, HIGH);
  digitalWrite(out_4,LOW);
}

void back(){
  digitalWrite(out_1, LOW);
  digitalWrite(out_2, HIGH); 
  digitalWrite(out_3, LOW);
  digitalWrite(out_4,HIGH);
}

void left(){
  analogWrite(out_1, 130);
  analogWrite(out_2, 0); 
  analogWrite(out_3, 0);
  analogWrite(out_4, 130);
}

void right(){
  analogWrite(out_1, 0);
  analogWrite(out_2, 130); 
  analogWrite(out_3, 130);
  analogWrite(out_4, 0);
}
