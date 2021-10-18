//functions for lighting 
//fill_solid turns all leds 1 colour based on the rgb value in ()

void white(){
  fill_solid( leds, NUM_LEDS, CRGB(255,255,255)); //fill led to rgb value
  FastLED.show(); //sets the led to set colour
}

void red(){
  fill_solid( leds, NUM_LEDS, CRGB(255,0,0));
  FastLED.show();
}

void blue(){
  fill_solid( leds, NUM_LEDS, CRGB(0,0,255));
  FastLED.show();
}

void orange(){
  fill_solid( leds, NUM_LEDS, CRGB(200,100,0));
  FastLED.show();
}
void green(){
  fill_solid( leds, NUM_LEDS, CRGB(0,255,0));
  FastLED.show();
}
void black(){
  fill_solid( leds, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
}
void purple(){
  fill_solid( leds, NUM_LEDS, CRGB(37,100,145));
  FastLED.show();
}

void multiCol(){
  fill_rainbow(leds, NUM_LEDS, 0, 255);
  FastLED.show();
}


void flash(){  
  for(int i = 0; i < 5; i++){ //for loop repeats 5 times
    blue(); //go blue for 200 milliseconds
    delay(200); 
    black(); //no colour for 200 milliseconds
    delay(200);
  }
}
