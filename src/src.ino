
#include <FastLED.h>
#include <HardwareSerial.h>

#include "config.h"
#include "states.hpp"
#include "animations.hpp"


// Function prototypes
void setupPins();
void checkSignals();

void setup() {

    Serial1.begin(115200);

    // Setup LEDs
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(0);

    // Setup pins
    setupPins();

    // Start with initial animation
    initialAnimation();
}

void loop() {

    // Echo serial
    if (Serial1.available()){
        Serial1.write(Serial1.read());
    }

    // Adjust brightness based on low beam status only if there's a state change
    if (isLowBeamActive() != lowBeamState) {
        lowBeamState = !lowBeamState;
        adjustBrightness();
    }
    // Perform turn signal animation if active

    if (turnSignalActive) {
        turnSignalAnimation();
        fill_solid(leds, NUM_LEDS, COLOR_DRL);
        adjustBrightness();
    }
}

void setupPins() {
    pinMode(LOW_BEAM_PIN, INPUT);
    // TODO: Attach an interrupt to low bean
    pinMode(TURN_SIGNAL_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(TURN_SIGNAL_PIN), []() {
        if (turnSignalActive) {
            return;  // Ignore incomming turn signals if is in turn mode (a kind of debounce)
        }
        lastTurnSignalTime = millis();
        turnSignalActive = true;
    }, RISING);
}

