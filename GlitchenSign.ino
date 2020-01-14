#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
	#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN			6
#define NUMPIXELS	21  // 7 pixels * 3 rows

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
	pixels.begin();
	pixels.clear();
}

void loop() {
	for(int i=0; i<NUMPIXELS; i++) {
		pixels.setPixelColor(i, pixels.Color(0, 150, 0));
		pixels.show();
		delay(500);
	}
}

