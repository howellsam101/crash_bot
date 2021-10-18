
int ultrasonic(){ //ultrasonic function that returns as int type
 
  for(int i=0; i<=180; i++){  //repeats 180 times 
    
    Servo1.write(i); //sets the angle of servo to value of i
    delay(30); //wait for 30 milliseconds
    distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    
    if (distance < 20){ //if distance under 20cm 
      //int Angle = i;
      return i; //returns i (the angle of servo)
      
    }
    if (i > 179){ //if angle over 179 without detection
      nothingDetected = true; //set nothingDetected to true
      return; //returns nothing
    }
  }
}

int calculateDistance(){ // function to read distance returns an int 
  digitalWrite(trigPin, LOW); //connnects trig pin to ground
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  //enables trig pin for 10 milliseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //disable trig pin
  long duration = pulseIn(echoPin, HIGH); //Recives pulse on echoPin and store as a long data type named duration 
  distance= duration*0.034/2; //caluates distance in cm 
  return distance; //returns distance
}

int ultrasonic_check(){
  Servo1.write(90); //set servo to 90 degrees
  distance = calculateDistance(); //calls function to check the distace
  return distance; //returns distance
}

void detected(){
  Stop(); //stops all motors 
  red(); //makes leds red
  tone(11, 1000, 1000); //sounds buzzer for 1 second
  delay(1000);
  distance = ultrasonic_check(); //gets distance 
  if (distance <= 40){ //checks if distance less than 40cm
     red(); 
     ahead(); //call function to drive foreward for 2 seconds 
     delay(1000); 
     orange(); //sets leds orange
     tone(buzzer, 4000,1000); 
     back(); //calls function to reverse motor direction for 2s
     delay(1000);
     Stop(); //stop motor 
  }
  return; //return to void loop without a value 
}
