
void Standby(){
  Stop(); // calls stop function
  Pause = true; //sets pause to true
  Serial.println("Standby mode");
  flash(); //call flash function
  
  while(Pause == true){ //repeats as long as pasue == true
    if (irrecv.decode(&results)){ //runs if recieves somthing from remote
        Serial.println("receiving...");
        Serial.print("received code: ");
        Serial.println((results.value), HEX);
        irrecv.resume();
        if (results.value == onOff){ //if recived hex value matches onOff
          Serial.println("Exiting Standby mode");
          tone(buzzer, 1000, 1000);
          Pause = false;  //sets pause to false
          break; //exit while loop
        }
    }
    multiCol(); //call multicolour function
  }
}

void Stop(){
  //ground all hbridge pins
  digitalWrite(out_1, LOW); 
  digitalWrite(out_2, LOW); 
  digitalWrite(out_3, LOW);
  digitalWrite(out_4, LOW);
}

void ahead(){
  analogWrite(out_1, 210); 
  analogWrite(out_2, 0); 
  analogWrite(out_3, 210);
  analogWrite(out_4,0);
}

void back(){
  analogWrite(out_1, 0);
  analogWrite(out_2, 180); 
  analogWrite(out_3, 0);
  analogWrite(out_4, 180);
}

void left(){
  analogWrite(out_1, 180);
  analogWrite(out_2, 0); 
  analogWrite(out_3, 0);
  analogWrite(out_4, 180);
}

void right(){
  analogWrite(out_1, 0);
  analogWrite(out_2, 180); 
  analogWrite(out_3, 180);
  analogWrite(out_4, 0);
}

void Move(){
   Stop(); //stop motors for 100 milliseconds
   delay(100);
   ahead(); //go forwards fro 1 second 
   delay(1000);
   left(); //turn left for 1 second
   delay(1000);
   Stop(); 
}
