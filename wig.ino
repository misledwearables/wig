#include <Adafruit_NeoPixel.h>

#define PIN 0

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  rainbowCycle(10);
  SPARKLE4EVA_CYCLE(6);
  rainbowFlash(300, 3);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void SPARKLE4EVA_CYCLE(int times) {
 for (int x = 0; x<times; x++) {
  SPARKLE4EVA(10);
  SPARKLE4EVA(50);
  SPARKLE4EVA(100);
  SPARKLE4EVA(150);
  SPARKLE4EVA(300);
  
  SPARKLE4EVA(300);
  SPARKLE4EVA(150);
  SPARKLE4EVA(100);
  SPARKLE4EVA(50);
 } 
}

void SPARKLE4EVA(int wait) {
  int white = strip.Color(255, 255, 255);
  int off = strip.Color(0, 0, 0);
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {    
      strip.setPixelColor(i, white);
      strip.show();
      delay(wait);
      
      strip.setPixelColor(i, off);
      strip.show();
  }
}

void rainbowFlash(int wait, int times) {
 
  int red = strip.Color(255, 0, 0);
  int orange = strip.Color(255, 100, 0);
  int yellow = strip.Color(255, 255, 0);
  int green = strip.Color(0, 255, 0);
  int blue = strip.Color(0, 0, 255);
  int indigo = strip.Color(75, 0, 130);
  int violet = strip.Color(238, 58, 140);

  for (int x=0; x<times; x++) {   
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorflash(yellow, wait);
    colorflash(orange, wait);
    colorflash(green, wait);
    colorflash(blue, wait);
    colorflash(indigo, wait);
    colorflash(violet, wait);
  }
}

void colorflash(int color, int wait) {
  int off = strip.Color(0, 0, 0);
  
  for(uint16_t i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);
    strip.show();
  }
  
  delay(wait);
  
  for(uint16_t i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, off);
    strip.show();
  }
  
  delay(wait);
  
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

