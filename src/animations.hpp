#ifndef ANIMATIONS_HPP
#define ANIMATIONS_HPP

#include "config.h"
#include "states.hpp"


// Function prototypes for animations
void refreshDRL();
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
    fill_solid(leds, NUM_LEDS, COLOR_OFF);
    FastLED.show();
}


// Set the default DRL color and target brightness
void refreshDRL() {
    Serial1.println(__func__);
    fill_solid(leds, NUM_LEDS, COLOR_DRL);
    FastLED.setBrightness(getTargetBrightness(lowBeamState));
    FastLED.show();
}


void initialAnimation() {
    Serial1.println(__func__);
    
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

    resetStrip();

    TURN_ANIMATION_FUNC();

    // Declare as done, this way a new animation can be queued
    turnSignalActive = false;

    // Await the time for completion
    unsigned long spentTime = millis() - turnMillis;
    if (spentTime < TURN_SIGNAL_DURATION) {
        delay(TURN_SIGNAL_DURATION - spentTime);
    }

    // Reset to baseline state
    refreshDRL();
}


void fade(unsigned char initialBrightness, unsigned char finalBrightness) {
    Serial1.println(__func__);
    // Determine the direction of the fade based on initial and final brightness
    int fadeStep = (initialBrightness < finalBrightness) ? FADE_STEP : -FADE_STEP;

    // Iterate over brightness levels from initial to final
    for (int brightness = initialBrightness;
            (fadeStep > 0 && brightness <= finalBrightness) || (fadeStep < 0 && brightness >= finalBrightness);
            brightness += fadeStep) {
        FastLED.setBrightness(brightness);
        fill_solid(leds, NUM_LEDS, COLOR_DRL);
        FastLED.delay(INITIAL_ANIMATION_SPEED);
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
        FastLED.delay(TURN_SIGNAL_ANIMATION_SPEED);
    }
}

void rgbSet() {
    Serial1.println(__func__);
    static uint8_t hue;
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < NUM_LEDS / 2; i++) {
            // fade everything out
            leds.fadeToBlackBy(10);

            // let's set an led value
            leds[i] = CHSV(hue++, 255, 255);

            // now, let's first 20 leds to the top 20 leds,
            leds(NUM_LEDS / 2, NUM_LEDS - 1) = leds(NUM_LEDS / 2 - 1, 0);
            FastLED.delay(TURN_SIGNAL_ANIMATION_SPEED);
        }
    }
}

#endif // ANIMATIONS_HPP
