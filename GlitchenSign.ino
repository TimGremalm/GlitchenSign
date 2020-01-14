#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
	#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN				6
#define NUMPIXELS		21  // 7 pixels * 3 rows

#define SECTION_LEN		7
#define SECTION_FG		0
#define SECTION_BG		7
#define SECTION_SMILEY	14

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

typedef enum {
	LIGHT_SOLID = 0,
	LIGHT_GLITCH = 1,
} light_mode_t;

light_mode_t current_mode;
unsigned long light_start = millis();

// Colors
uint8_t brightness = 85;
uint32_t colorfg		= pixels.ColorHSV(6000,		255,	20);
uint32_t colorbg		= pixels.ColorHSV(32000,	255,	0);
uint32_t colorsmiley	= pixels.ColorHSV(32000,	255,	brightness);
uint32_t colorblack		= pixels.Color(0, 0, 0);

void setup() {
	Serial.begin (115200);
	pixels.begin();
	pixels.clear();
	Serial.println("GlitchenSign Start");
}

void printMode() {
	Serial.print("Mode: ");
	Serial.println(current_mode);
}

void calcMode() {
	unsigned long diff = millis() - light_start;
	switch(current_mode) {
		case LIGHT_SOLID:
			if (diff > 3000) {
				current_mode = LIGHT_GLITCH;
				light_start = millis();
				printMode();
			}
			break;
		case LIGHT_GLITCH:
			if (diff > 800) {
				current_mode = LIGHT_SOLID;
				light_start = millis();
				printMode();
			}
			break;
	}
}

void tick() {
	switch(current_mode) {
		case LIGHT_SOLID:
			for(int i=0; i<NUMPIXELS; i++) {
				if (i>=SECTION_FG && i<SECTION_FG+SECTION_LEN) {
					pixels.setPixelColor(i, colorfg);
				}
				if (i>=SECTION_BG && i<SECTION_BG+SECTION_LEN) {
					pixels.setPixelColor(i, colorblack);
				}
				if (i>=SECTION_SMILEY && i<SECTION_SMILEY+SECTION_LEN) {
					pixels.setPixelColor(i, colorbg);
				}
			}
			break;
		case LIGHT_GLITCH:
			for(int i=0; i<NUMPIXELS; i++) {
				if (i>=SECTION_FG && i<SECTION_FG+SECTION_LEN) {
					pixels.setPixelColor(i, colorfg);
				}
				if (i>=SECTION_BG && i<SECTION_BG+SECTION_LEN) {
					pixels.setPixelColor(i, colorsmiley);
				}
				if (i>=SECTION_SMILEY && i<SECTION_SMILEY+SECTION_LEN) {
					pixels.setPixelColor(i, colorbg);
				}
			}
			break;
	}
	pixels.show();
}

void loop() {
	calcMode();
	tick();
	delay(20);
}

