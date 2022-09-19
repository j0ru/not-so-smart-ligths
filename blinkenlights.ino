#include <FastLED.h>

#define NUM_LEDS 60      /* The amount of pixels/leds you have */
#define DATA_PIN 7       /* The pin your data line is connected to */
#define LED_TYPE WS2812B /* I assume you have WS2812B leds, if not just change it to whatever you have */
#define BRIGHTNESS 255   /* Control the brightness of your leds */
#define SATURATION 255   /* Control the saturation of your leds */

#define STEP_DELAY 500

CRGB leds[NUM_LEDS];

/**
 * Hardware access functions.
 *
 * (c) 2021 Thomas Smits
 */

#include "types.h"

/* Pins for DIP switch */
#define DIP0_PIN 25
#define DIP1_PIN 33
#define DIP2_PIN 32
#define DIP3_PIN 35

/* Pin the neopixel stripe is attached to */
#define DATA_PIN 4

/* Type of LED stripe */
#define LED_TYPE    WS2811

/* Order of the colors in the data */
#define COLOR_ORDER GRB

/**
 * Initialize the hardware.
 */
void setup_hardware() {
    // set the DIP switch pins to input and activate internal
    // pulldown resistor
    pinMode(DIP0_PIN, INPUT_PULLDOWN);
    pinMode(DIP1_PIN, INPUT_PULLDOWN);
    pinMode(DIP2_PIN, INPUT_PULLDOWN);
    pinMode(DIP3_PIN, INPUT_PULLDOWN);

    // Initialize FastLED lib
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
}

/**
 * Get the devices ID by reading the setting
 * of the DIP switch connected to the ports
 * defined by the constants.
 *
 * @return the id of the device as set by the
 */
uint get_id() {

    int p0 = digitalRead(DIP0_PIN);
    int p1 = digitalRead(DIP1_PIN);
    int p2 = digitalRead(DIP2_PIN);
    int p3 = digitalRead(DIP3_PIN);

    uint id = (uint) (p0 + (p1 * 2) + (p2 * 4) + (p3 * 8));

    return id;
}

void setup() {
  setup_hardware();
}

void loop() {
  for (int j = 0; j < 255; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); /* The higher the value 4 the less fade there is and vice versa */ 
    }
    FastLED.show();
    delay(STEP_DELAY); /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
  }
}
