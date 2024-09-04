/*
	CardKB_to_USB
*/

#include <M5Unified.h>

#include <USB.h>
#include <USBHIDKeyboard.h>
USBHIDKeyboard Keyboard;


#include <FastLED.h>
#define PIN_BUTTON 0    // main button（G0）
#define PIN_LED    21   // RGB LED（G21）
#define NUM_LEDS   1    // RGB LED count
CRGB leds[NUM_LEDS];


#include <SPI.h>
#include <Wire.h>
#define CARDKB_ADDR 0x5F  // Define the I2C address of CardKB.

//	CardKB layout
#define	CARDKB_ESC			0x1B
#define	CARDKB_UP				0xB5
#define	CARDKB_DOWN			0xB6
#define	CARDKB_LEFT			0xB4
#define	CARDKB_RIGHT		0xB7
#define	CARDKB_RETURN		0x0d
#define	CARDKB_TAB			0x09
#define	CARDKB_BS				0x08
#define	CARDKB_F1				0x81
#define	CARDKB_F12			(CARDKB_F1 + 11)

#define	BLINK_INTERVAL		100000

enum mode {			// BUTTON input mode
	Normal,
	Ctrl,
	Alt
};

void blink_led(long interval, CRGB color) {
	static long LEDTimer;
  long currentTime = micros();
	
	if (currentTime - LEDTimer > interval) {
		LEDTimer = currentTime;
		if(leds[0] == CRGB::Black) leds[0] = color;
		else leds[0] = CRGB::Black;
	}	
	FastLED.show();
}


void mode_led(int mode) {

	switch(mode) {
		case Normal	:leds[0] = CRGB::Blue; FastLED.show();		break;
		case Ctrl		:blink_led(BLINK_INTERVAL, CRGB::Red);		break;
		case Alt		:blink_led(BLINK_INTERVAL, CRGB::Green);	break;
	}
	FastLED.show();
}


int button_check(int mode) {	
	if (!digitalRead(PIN_BUTTON)) {
		delay(5);
		if (!digitalRead(PIN_BUTTON)) {
			mode++;
			if (mode > Alt) mode = Normal;
			while (!digitalRead(PIN_BUTTON));
		}
	}
	
	return mode;
}

void kb_write(int mode, int key) {
	switch(mode) {
		case 1: Keyboard.press(KEY_LEFT_CTRL);		break;
		case 2: Keyboard.press(KEY_LEFT_ALT);			break;
	}
	Keyboard.press(key);
	Keyboard.releaseAll();
}



void setup() {
 // Serial.begin(115200);	
	
	M5.begin(); 
	
	Keyboard.begin();
  USB.begin();
	
	pinMode(PIN_BUTTON, INPUT);

	// RGB LEDs on
	FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS);	// RGB LED init
	FastLED.clear();  // clear all pixel data
  FastLED.setBrightness(7);
  leds[0] = CRGB::White;
  FastLED.show();

	// join i2c bus (address optional for master)
	Wire.begin();

}

void loop() {
	static int mode = Normal;
	
	mode = button_check(mode);
	mode_led(mode);
	
	Wire.requestFrom(CARDKB_ADDR, 1);     // Request 1 byte from the slave device.

	while (Wire.available())  						// If received data is detected.
	{
		byte key = Wire.read(); 						// Store the received data.
		if (key != 0) {
			// Serial.printf("[%c] : %x\n",key, key);
			switch(key) {
				case CARDKB_ESC			:kb_write(mode, KEY_ESC);						break;
				case CARDKB_UP			:kb_write(mode, KEY_UP_ARROW);			break;
				case CARDKB_DOWN		:kb_write(mode, KEY_DOWN_ARROW);		break;
				case CARDKB_LEFT		:kb_write(mode, KEY_LEFT_ARROW);		break;
				case CARDKB_RIGHT		:kb_write(mode, KEY_RIGHT_ARROW);		break;
				case CARDKB_RETURN	:kb_write(mode, KEY_RETURN);				break;
				case CARDKB_TAB			:kb_write(mode, KEY_TAB);						break;
				case CARDKB_BS			:kb_write(mode, KEY_DELETE);				break;	// <bs> -> <del>
				default:	
					if(key >= CARDKB_F1 && key <= CARDKB_F12)
							kb_write(mode, (key - CARDKB_F1) + KEY_F1); 		// f1..f12
					else kb_write(mode, key);
			}
			mode = Normal;
		}
	}
	
}