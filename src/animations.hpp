#ifndef ANIMATIONS_HPP
#define ANIMATIONS_HPP

#include "config.h"
#include "states.hpp"


// Function prototypes for animations
void adjustBrightness();
void setBrightness(unsigned char brightness);
void initialAnimation();
void finalAnimation();
void turnSignalAnimation();
void fade(unsigned char initialBrightness, unsigned char finalBrightness);
void fadeIn();
void fadeOut();
void turnSequential();
void rgbSet();


void resetStrip() {
    Serial1.println(__func__);
    memset8( leds, COLOR_OFF, NUM_LEDS * sizeof(CRGB));
    FastLED.show();
}


// Adjust brightness based on low beam signal only if there's a state change
void adjustBrightness() {
    Serial1.println(__func__);
    setBrightness(getTargetBrightness(lowBeamState));
}

void setBrightness(unsigned char brightness){
    FastLED.setBrightness(brightness);
    FastLED.show();
}


void initialAnimation() {
    Serial1.println(__func__);
    // Select initial animation based on type
    INITIAL_ANIMATION_FUNC();
}


void finalAnimation() {
    Serial1.println(__func__);
    FINAL_ANIMATION_FUNC();
}


void turnSignalAnimation() {
    Serial1.println(__func__);
    // Animate a sequential turn signal
    unsigned long turnMillis = millis();

    fill_solid(leds, NUM_LEDS, COLOR_OFF);

    TURN_ANIMATION_FUNC();

    // Declare as done, this way a new animation can be queued
    turnSignalActive = false;

    // Await the time for completion
    unsigned long spentTime = millis() - turnMillis;
    if (spentTime < TURN_SIGNAL_DURATION) {
        delay(TURN_SIGNAL_DURATION - spentTime);
    }
}


void fade(unsigned char initialBrightness, unsigned char finalBrightness) {
    Serial1.println(__func__);
    // Determine the direction of the fade based on initial and final brightness
    int fadeStep = (initialBrightness < finalBrightness) ? FADE_STEP : -FADE_STEP;
    Serial1.print("fadeStep: ");
    Serial1.println(fadeStep);
    Serial1.print("initialBrightness: ");
    Serial1.println(initialBrightness);
    Serial1.print("finalBrightness: ");
    Serial1.println(finalBrightness);

    // Iterate over brightness levels from initial to final
    for (int brightness = initialBrightness;
            (fadeStep > 0 && brightness <= finalBrightness) || (fadeStep < 0 && brightness >= finalBrightness);
            brightness += fadeStep) {
        FastLED.setBrightness(brightness);
        Serial1.println(brightness);
        fill_solid(leds, NUM_LEDS, COLOR_DRL);
        FastLED.show();
        delay(INITIAL_ANIMATION_SPEED);
    }

    // Ensure finalBrightness is reached
    FastLED.setBrightness(finalBrightness);
    fill_solid(leds, NUM_LEDS, COLOR_DRL);
    FastLED.show();
}


void fadeIn() {
    Serial1.println(__func__);
    fade(0, getTargetBrightness()); // Fade from 0 to target brightness
}


void fadeOut() {
    Serial1.println(__func__);
    fade(getTargetBrightness(), 0); // Fade from target brightness to 0
}


void turnSequential() {
    Serial1.println(__func__);
    // Shift LEDs for sequential effect
    FastLED.setBrightness(TURN_BRIGHTNESS);
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = COLOR_TURN_SIGNAL;
        FastLED.show();
        delay(TURN_SIGNAL_ANIMATION_SPEED);
    }
}

void rgbSet() {
    Serial1.println(__func__);
    static uint8_t hue;
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < NUM_LEDS / 2; i++) {
            // fade everything out
            leds.fadeToBlackBy(40);

            // let's set an led value
            leds[i] = CHSV(hue++, 255, 255);

            // now, let's first 20 leds to the top 20 leds,
            leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
            FastLED.delay(TURN_SIGNAL_ANIMATION_SPEED);
        }
    }
}

#endif // ANIMATIONS_HPP
