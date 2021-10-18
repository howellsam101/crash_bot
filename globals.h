//import libraries
#include <pt.h>
#include <IRremote.h>
#include "FastLED.h"
#include <Servo.h>  

//defines all arduino pins 
#define DATA_PIN 7 //pin leds connected to
#define enable 2 //pin for enable
#define out_1 3 
#define out_2 4 
#define out_3 5 
#define out_4 6 
#define servoPin 12
#define buzzer 11 //buzzer pin 
#define trigPin 9 //pin to connect Trig 
#define echoPin 10 //pin to connect echo
#define RECV_PIN A5 //pin connected to ir reciver 

//defines global variables
#define onOff 0xFFC23D 
#define LED_TYPE WS2811 //type of leds used in strip
#define COLOR_ORDER GRB //color order red, green, blue
#define NUM_LEDS 10 //number of leds in strip
#define BRIGHTNESS 50 //brigthness level of leds

bool Pause = true; 
bool nothingDetected = false; 
int distance; 
//unsigned long previousMillis = 0; //long value to store time
//const long interval = 1000; //time to change light colour
IRrecv irrecv(RECV_PIN);
decode_results results;
CRGB leds[NUM_LEDS]; //numbers the leds from 0 to 9
Servo Servo1;
