#ifndef CONFIG_H
#define CONFIG_H


// LED strip configuration
#define LED_PIN PB12             // Pin for the LED strip
#define NUM_LEDS 144             // Number of LEDs on the strip
#define LED_TYPE WS2812B         // Type of LED strip
#define COLOR_ORDER RGB          // Color order for the strip
#define BRIGHTNESS  12           // Max brightness for daytime running lights
#define TURN_BRIGHTNESS  4       // Brightness for turn signal
#define LOW_BEAM_BRIGHTNESS  6   // Brightness when low beam is active (usualy lower than normal brightness)

// Pin configuration
#define TURN_SIGNAL_PIN PB11         // Pin connected to turn signal
#define LOW_BEAM_PIN PB10            // Pin connected to low beam signal

// Animation settings
#define INITIAL_ANIMATION_SPEED 50      // Delay between frames in the initial animation (ms)
#define FINAL_ANIMATION_SPEED 50        // Delay between frames in the final animation (ms)
#define TURN_SIGNAL_ANIMATION_SPEED 0  // Delay between frames in the turn signal animation (ms)
#define TURN_SIGNAL_DURATION 2000       // Duration of the turn signal animation (ms)
#define FADE_STEP 1

// Animation selector
#define INITIAL_ANIMATION_FUNC rgbSet            // Select initial animation function
#define FINAL_ANIMATION_FUNC fadeOut             // Select final animation function
#define TURN_ANIMATION_FUNC turnSequential       // Select turn animation function

// Define colors
#define COLOR_DRL CRGB::White           // Color for daytime running lights
#define COLOR_OFF CRGB::Black           // Color when it is off (transitions)
#define COLOR_TURN_SIGNAL CRGB::Orange  // Color for turn signal

#endif // CONFIG_H
