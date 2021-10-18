#include "globals.h"

void setup() {
  // put your setup code here, to run once:
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); //limit to 5v and 500mA
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); //configure led strip
  FastLED.setBrightness(BRIGHTNESS); //set brightness
  
  //defines all output pins as either inputs or outputs
  pinMode(out_1, OUTPUT);
  pinMode(out_2, OUTPUT);
  pinMode(out_3, OUTPUT);
  pinMode(out_4, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(RECV_PIN, INPUT);
  pinMode(DATA_PIN, OUTPUT);
  Servo1.attach(servoPin);
  irrecv.enableIRIn();
  Serial.begin(9600); //starts the serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Pause == true)Standby(); //if pause is true exicute standby
  
  Stop(); //stop motors 
  green(); //calls function to turn leds green
  int Angle = ultrasonic(); //store returning integer from ultrasonic as distance
  Serial.print("angle: ");
  Serial.println(Angle);
  
  if ((nothingDetected == false)&&(Angle >= 110)){ //if angle is more than 110
    Serial.println("left");
    left(); //function to turn robot left
    delay(200); //stop for 200 milliseconds 
    Stop(); //stop motors 
  }
  
  if ((nothingDetected == false)&&(Angle <= 70)){ //if angle is less than 70
    Serial.print("right");
    right(); //turn right for 100 milliseconds
    delay(100);
    Stop(); //stop motors
  }
  
  if ((Angle > 80)&&(Angle < 100)){ //if angle between 80 and 100
    Serial.println("detected");
    detected(); //execute detected funtoon
  }
  
  if (nothingDetected == true){ //if nothing is detected
    Serial.println("relocating");
    Move(); //execute move function to relocaate robot 
    nothingDetected = false; //nothingdetected to false
  }
}
