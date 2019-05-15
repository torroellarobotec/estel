#include <FastLED.h>

#define LED_PIN  5

#define COLOR_ORDER GRB
#define CHIPSET     WS2812

#define BRIGHTNESS 255
int x = 0;
int y1 = -1;
int y2 = -1;
int y3 = -1;
int x1 = -1;
int x2 = -1;
int x3 = -1;


int base = 0;
int direccio = 1;

// Helper functions for an two-dimensional XY matrix of pixels.
// Simple 2-D demo code is included as well.
//
//     XY(x,y) takes x and y coordinates and returns an LED index number,
//             for use like this:  leds[ XY(x,y) ] == CRGB::Red;
//             No error checking is performed on the ranges of x and y.
//
//     XYsafe(x,y) takes x and y coordinates and returns an LED index number,
//             for use like this:  leds[ XY(x,y) ] == CRGB::Red;
//             Error checking IS performed on the ranges of x and y, and an
//             index of "-1" is returned.  Special instructions below
//             explain how to use this without having to do your own error
//             checking every time you use this function.
//             This is a slightly more advanced technique, and
//             it REQUIRES SPECIAL ADDITIONAL setup, described below.


// Params for width and height
const uint8_t kMatrixWidth = 30;
const uint8_t kMatrixHeight = 30;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
// Set 'kMatrixSerpentineLayout' to false if your pixels are
// laid out all running the same way, like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//     .----<----<----<----'
//     |
//     5 >  6 >  7 >  8 >  9
//                         |
//     .----<----<----<----'
//     |
//    10 > 11 > 12 > 13 > 14
//                         |
//     .----<----<----<----'
//     |
//    15 > 16 > 17 > 18 > 19
//
// Set 'kMatrixSerpentineLayout' to true if your pixels are
// laid out back-and-forth, like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//                         |
//     9 <  8 <  7 <  6 <  5
//     |
//     |
//    10 > 11 > 12 > 13 > 14
//                        |
//                        |
//    19 < 18 < 17 < 16 < 15
//
// Bonus vocabulary word: anything that goes one way
// in one row, and then backwards in the next row, and so on
// is call "boustrophedon", meaning "as the ox plows."


// This function will return the right 'led index number' for
// a given set of X and Y coordinates on your matrix.
// IT DOES NOT CHECK THE COORDINATE BOUNDARIES.
// That's up to you.  Don't pass it bogus values.
//
// Use the "XY" function like this:
//
//    for( uint8_t x = 0; x < kMatrixWidth; x++) {
//      for( uint8_t y = 0; y < kMatrixHeight; y++) {
//
//        // Here's the x, y to 'led index' in action:
//        leds[ XY( x, y) ] = CHSV( random8(), 255, 255);
//
//      }
//    }
//
//
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;

  if ( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if ( kMatrixSerpentineLayout == true) {
    if ( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }

  return i;
}


// Once you've gotten the basics working (AND NOT UNTIL THEN!)
// here's a helpful technique that can be tricky to set up, but
// then helps you avoid the needs for sprinkling array-bound-checking
// throughout your code.
//
// It requires a careful attention to get it set up correctly, but
// can potentially make your code smaller and faster.
//
// Suppose you have an 8 x 5 matrix of 40 LEDs.  Normally, you'd
// delcare your leds array like this:
//    CRGB leds[40];
// But instead of that, declare an LED buffer with one extra pixel in
// it, "leds_plus_safety_pixel".  Then declare "leds" as a pointer to
// that array, but starting with the 2nd element (id=1) of that array:
//    CRGB leds_with_safety_pixel[41];
//    CRGB* const leds( leds_plus_safety_pixel + 1);
// Then you use the "leds" array as you normally would.
// Now "leds[0..N]" are aliases for "leds_plus_safety_pixel[1..(N+1)]",
// AND leds[-1] is now a legitimate and safe alias for leds_plus_safety_pixel[0].
// leds_plus_safety_pixel[0] aka leds[-1] is now your "safety pixel".
//
// Now instead of using the XY function above, use the one below, "XYsafe".
//
// If the X and Y values are 'in bounds', this function will return an index
// into the visible led array, same as "XY" does.
// HOWEVER -- and this is the trick -- if the X or Y values
// are out of bounds, this function will return an index of -1.
// And since leds[-1] is actually just an alias for leds_plus_safety_pixel[0],
// it's a totally safe and legal place to access.  And since the 'safety pixel'
// falls 'outside' the visible part of the LED array, anything you write
// there is hidden from view automatically.
// Thus, this line of code is totally safe, regardless of the actual size of
// your matrix:
//    leds[ XYsafe( random8(), random8() ) ] = CHSV( random8(), 255, 255);
//
// The only catch here is that while this makes it safe to read from and
// write to 'any pixel', there's really only ONE 'safety pixel'.  No matter
// what out-of-bounds coordinates you write to, you'll really be writing to
// that one safety pixel.  And if you try to READ from the safety pixel,
// you'll read whatever was written there last, reglardless of what coordinates
// were supplied.

#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if ( x >= kMatrixWidth) return -1;
  if ( y >= kMatrixHeight) return -1;
  return XY(x, y);
}


// Demo that USES "XY" follows code below

void loop()
{
  uint32_t ms = millis();
  int32_t yHueDelta32 = ((int32_t)cos16( ms * (27 / 1) ) * (350 / kMatrixWidth));
  int32_t xHueDelta32 = ((int32_t)cos16( ms * (39 / 1) ) * (310 / kMatrixHeight));
  pintaNau();
  pintaFoc();
  if ( ms < 5000 ) {
    FastLED.setBrightness( scale8( BRIGHTNESS, (ms * 256) / 5000));
  } else {
    FastLED.setBrightness(BRIGHTNESS);
  }
  FastLED.show();
  delay(200);

  x = x + direccio;
  if (x > 25)
  {
    x = 24;
    direccio = -1;
  }
  if (x<0)
  {
    x=0;
    direccio=1;
  }
  if (x==3)
  {
    y1=27;
    x1=5;
  }
  if (x==12)
  {
    y2=27;
    x2=14;
  }
}
void pintaFoc()
{
  if (y1!=-1)
  {
    leds[ XY(x1, y1)]  = CHSV( 0, 0, 0);
     leds[ XY(x1, y1-1)]  = CRGB::Red;
      leds[ XY(x1, y1-2)]  = CRGB::Red;
      y1=y1-1;
      if (y1<0) y1=-1;
  }
  if (y2!=-1)
  {
    leds[ XY(x2, y2)]  = CHSV( 0, 0, 0);
     leds[ XY(x2, y2-1)]  = CRGB::Red;
      leds[ XY(x2, y2-2)]  = CRGB::Red;
      y2=y2-1;
      if (y2<0) y2=-1;
  }
}

void pintaNau()


{
  if (direccio == 1)
  {
    if (x > 0)
    {
      //esborro
      leds[ XY(x - 1, 29)]  = CHSV( 0, 0, 0);
      leds[ XY(x - 1, 28)]  = CHSV( 0, 0, 0);
      leds[ XY(x + 1, 27)]  = CHSV( 0, 0, 0);
    }


    
  }
  else
  {
    if (x <25)
    {
      //esborro
      leds[ XY(x + 5, 29)]  = CHSV( 0, 0, 0);
      leds[ XY(x + 5, 28)]  = CHSV( 0, 0, 0);
      leds[ XY(x +3, 27)]  = CHSV( 0, 0, 0);
    }
  }

  byte pixelHue = 120;
    //pinto
    leds[ XY(x, 29)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x + 1, 29)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x + 2, 29)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x + 3, 29)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x + 4, 29)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x, 28)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x + 1, 28)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x + 2, 28)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x + 3, 28)]  = CHSV( pixelHue, 255, 255);
    leds[ XY(x + 4, 28)]  = CHSV( pixelHue, 255, 255);

    leds[ XY(x + 2, 27)]  = CHSV( pixelHue, 255, 255);
  



}

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
}
