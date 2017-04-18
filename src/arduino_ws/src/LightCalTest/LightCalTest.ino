#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 12

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(57600);
	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void loop() { 
	static uint8_t hue = 0;
//	Serial.print("x");
	// First slide the led in one direction
	for(int i = 0; i < 4; i++) {
		// Set the i'th led to red 
		leds[i] = CHSV(160, 255, 255);
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		// Wait a little bit before we loop around and do it again
	}

 for(int i = 4; i < 8; i++) {
   // Set the i'th led to red 
    leds[i] = CHSV(96, 255, 255);
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    // Wait a little bit before we loop around and do it again
  }

  for(int i = 8; i < 12; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(0, 255, 255);
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    // Wait a little bit before we loop around and do it again
  }
 
   FastLED.show(); 
}
