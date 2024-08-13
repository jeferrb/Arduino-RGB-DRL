# Arduino RGB LED Strip Controller

This project uses an Arduino to control addressable RGB LED strips as dynamic daytime running lights (DRLs) and sequential turn signals for vehicles.
It enhances both the aesthetic and functional aspects of automotive lighting, offering customizable patterns and improved safety.
However it is not recomended to be used as a product in a real vehicle.

**Disclaimer:** Ensure you comply with local regulations and vehicle safety standards when using this library, as it may not be road legal in all jurisdictions.

## Features

- **Dynamic Daytime Running Lights (DRL):** Enhances visibility and aesthetics with customizable patterns and colors.
- **Sequential Turn Signals:** Provides turn signal animations for clear indications.
- **Automatic Brightness Adjustment:** Adjusts brightness based on the vehicle's low beam status.
- **Custom Animations:** Easily modify animations to suit personal preferences or vehicle styling.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno, Mega, etc.)
- Addressable RGB LED strip (e.g., WS2812B)
- Power supply compatible with your LED strip
- Connecting wires
- Resistors or diodes or optocouplers to monitor vehicle signals

## Pin Configuration

- **LED Strip Pin:** Pin connected to the data line of the LED strip
- **Turn Signal Pin:** Pin connected to the vehicle's turn signal
- **Low Beam Pin:** Pin connected to the vehicle's low beam signal

## Usage

### Initial Setup

1. **Power On:** Connect your Arduino to a power source and ensure the LED strip is properly connected.
2. **Initial Animation:** When the system powers up, it will display the initial animation defined in `initialAnimation()`.

### Turn Signal Operation

- **Activation:** The turn signal animation is triggered when the turn signal pin receives a high signal.
The animation will run for the duration defined in `TURN_SIGNAL_DURATION`.
- **Animation Behavior:** The LEDs will display a sequential turn signal effect, as specified in `turnSignalAnimation()`.

### Low Beam Adjustment

- **Automatic Brightness Adjustment:** The brightness of the LEDs is automatically adjusted based on the low beam status detected on the low beam pin.
- **Brightness Levels:** When the low beam is active, the brightness is set to `LOW_BEAM_BRIGHTNESS`.
Otherwise, it returns to the maximum brightness defined in `BRIGHTNESS`.

### Customization

To modify the animations, edit the `animations.hpp` file:

- **Initial Animation:** Customize the initial animation sequence in `initialAnimation()`.
- **Turn Signal Animation:** Modify the turn signal sequence in `turnSignalAnimation()`.
- **Shutdown Animation:** Define the LED shutdown sequence in `shutdownAnimation()` if needed.

Ensure you upload the updated code to your Arduino after making changes.

## Configuration

All configurations are done in `config.h`.
Adjust the following parameters according to your setup:

```cpp
// LED strip configuration
#define LED_PIN 6            // Pin for the LED strip
#define NUM_LEDS 30          // Number of LEDs on the strip
#define LED_TYPE WS2812B     // Type of LED strip
#define COLOR_ORDER GRB      // Color order for the strip
#define BRIGHTNESS 255       // Max brightness for daytime running lights
#define LOW_BEAM_BRIGHTNESS 64 // Brightness when low beam is on

// Pin configuration
#define TURN_SIGNAL_PIN 2    // Pin connected to turn signal
#define LOW_BEAM_PIN 3       // Pin connected to low beam signal

// Animation settings
#define INITIAL_ANIMATION_SPEED 50   // Delay between frames in the initial animation (ms)
#define TURN_SIGNAL_ANIMATION_SPEED 30 // Delay between frames in the turn signal animation (ms)
#define TURN_SIGNAL_DURATION 5000     // Duration of the turn signal animation (ms)

// Animation selector
#define INITIAL_ANIMATION_TYPE 1     // Select initial animation type (1, 2, 3, etc.)

// Define colors
#define COLOR_DRL CRGB::White        // Color for daytime running lights
#define COLOR_TURN_SIGNAL CRGB::Orange // Color for turn signal
```

## License

This project is licensed under the MIT License.
See the [LICENSE](LICENSE) file for details.

### MIT License Summary

- **Permission is granted** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software.
- **The software is provided "as is"** without warranty of any kind.
The authors are not liable for any damages arising from the use of the software.
- **You must include the license** in all copies or substantial portions of the Software.

For the full text of the MIT License, refer to the `LICENSE` file.

## Contribution

We welcome contributions to improve this project! If you have suggestions, improvements, or bug fixes.

## Reporting Issues
If you encounter any bugs or have feature requests, please open an issue in the Issues section of the repository.
Include a detailed description of the issue and steps to reproduce it.
