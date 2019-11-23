#include "FastLED.h"
#define UPDATES_PER_SECOND 100
#define NUM_LEDS 300 //60x60

#define DATA_PIN 7
#define BRIGHTNESS  120

// Define the array of leds
CRGB leds[ NUM_LEDS ];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void setup() {  
  delay( 3000 ); // power-up safety delay
  
  FastLED.addLeds<WS2813, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS );

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PintarEstrella(int estrella)
{
    for(int i=0; i<NUM_LEDS;i++)
    {
        //leds[i] = CRGB((Estrelles[estrella][i][0]), (Estrelles[estrella][i][1]), (Estrelles[estrella][i][2])); 
        //leds[i] = CHSV((Estrelles[estrella][i][0]), (Estrelles[estrella][i][1]), (Estrelles[estrella][i][2]));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EfecteCel(int estrella)
{
  int valor=0;  
  for(int i=0; i<20;i++)
  {
      valor=random(NUM_LEDS);

      /*if (Estrelles[estrella][valor][0]==0 and  Estrelles[estrella][valor][1]==0 and Estrelles[estrella][valor][2]==0)
      {
        //leds[valor] = CRGB(0,0,random(255));   
        leds[valor] = CHSV(240,100,random(100));
      }*/
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

void PintarEstrellaTiraPerTira(int estrella)
{
    for(int tira=0;tira<60;tira++)
    {
      for(int led=0; led<60;led++)
      {
        //leds[tira*60+led] = CHSV((Estrelles[estrella][tira*60+led][0]), (Estrelles[estrella][tira*60+led][1]), (Estrelles[estrella][tira*60+led][2]));        
      }
      FastLED.show();
      FastLED.delay(100);
    }    
}

////////////////////////////////////////////////////////////////////////////////////////////////

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}

// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};

/////////////////////////////////////////////////////////////////////////////////////////////

//Efecte Fade IN
void FadeIn(CRGB *_leds, int _cleds, int estrella)
{
  //Per cada un dels leds de la matriu  
  for(int i=0;i<_cleds;i++)
  {
      //Incrementem el valor de 0 a 125 (50%)
      //No el faig anar fins al 100% perquè seria com posar el brightness a 255
      for(int j=0;j>=125;j++)
      {
        //Col·loquem el nou valor de Hue i mostrem amb un petit delay    
        //_leds[i] = CHSV(Estrelles[estrella][i][0], Estrelles[estrella][i][1], j);
        EVERY_N_MILLIS(15)
        {
          FastLED.show();
        }
      }     
    }  
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Efecte Fade OUT
void FadeOut(CRGB *_leds, int _cleds, int estrella)
{
  //Per cada un dels leds de la matriu  
  for(int i=0;i<_cleds;i++)
  {
      //Incrementem el valor de 0 a 125 (50%)
      //No el faig anar fins al 100% perquè seria com posar el brightness a 255
      for(int j=125;j<=0;j--)
      {
        //Col·loquem el nou valor de Hue i mostrem amb un petit delay    
        //_leds[i] = CHSV(Estrelles[estrella][i][0], Estrelles[estrella][i][1], j);
        EVERY_N_MILLIS(15)
        {
          FastLED.show();
        }
      }     
    }  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

  /////////////////////////////////////// CUA ///////////////////////////////////////////////////////////

  EVERY_N_MILLIS(10)
  {
    ChangePalettePeriodically();  
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */  
    FillLEDsFromPaletteColors( startIndex);
  }

  /////////////////////////////////////// MATRIU /////////////////////////////////////////////////////////
    
  //Carreguem la imatge als leds de la matriu
  /*int NumEstrella = 1;
  
  PintarEstrella(NumEstrella);

  FadeIn(leds, NUM_LEDS, 1);

  FadeOut(leds, NUM_LEDS, 1);

  EVERY_N_MILLIS(1000){EfecteCel(NumEstrella); FastLED.show();}*/

}
