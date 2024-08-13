#ifndef STATES_HPP
#define STATES_HPP


// Function prototypes for states
volatile bool isLowBeamActive();
volatile unsigned char getTargetBrightness();
unsigned char getTargetBrightness(bool isLowBeamActive);

// Create LED array
CRGBArray<NUM_LEDS> leds;

// Variables to manage state
bool lowBeamState = false;  // Track the previous state of the low beam
volatile bool turnSignalActive = false;
volatile unsigned long lastTurnSignalTime = 0;
unsigned long previousRefreshMillis = 0;        // The last time a refresh happened


volatile bool isLowBeamActive() {
    // Check if the low beam signal is active
    return digitalRead(LOW_BEAM_PIN) == HIGH;
}


volatile unsigned char getTargetBrightness() {
    return getTargetBrightness(isLowBeamActive());
}


unsigned char getTargetBrightness(bool isLowBeamActive) {
    Serial1.print("getTargetBrightness: ");
    Serial1.print(isLowBeamActive);
    if (isLowBeamActive) {
        Serial1.println(LOW_BEAM_BRIGHTNESS);
        return LOW_BEAM_BRIGHTNESS;
    }
    Serial1.println(BRIGHTNESS);
    return BRIGHTNESS;
}

#endif // STATES_HPP
