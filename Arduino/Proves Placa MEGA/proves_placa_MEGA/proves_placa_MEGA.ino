#include "FastLED.h"
#define NUM_LEDS 300 
#define DATA_PIN 6 //Matriu
#define BRIGHTNESS  120

CRGB leds[ NUM_LEDS ];

void setup() {    
  delay( 3000 ); // power-up safety delay  
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS );
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<NUM_LEDS;i++)
  {
    leds[i] = CRGB(0,255,0);    
  }

  FastLED.show();
  delay(150);
}
