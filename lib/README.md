# X9C104P Arduino Library

A reusable Arduino C++ library for controlling the X9C104P digital potentiometer.

## Overview

The library provides an interface for initializing the X9C104P, homing the wiper, selecting a wiper position, and calculating nominal resistance values.

It is intended to simplify integration of the X9C104P into Arduino-based embedded systems.

## Features

- Initialization of digital control pins.
- Wiper homing.
- Position selection from 0 to 99.
- Software-based position tracking.
- Nominal resistance-to-position conversion.
- Position-to-nominal-resistance calculation.

## Installation in PlatformIO

Copy the `X9C104P` library directory into the `lib/` directory of your PlatformIO project.

The resulting structure should include:

```text
your-project/
├── platformio.ini
├── src/
│   └── main.cpp
└── lib/
    └── X9C104P/
        ├── library.json
        ├── README.md
        ├── src/
        │   ├── X9C104P.h
        │   └── X9C104P.cpp
        └── examples/
            └── basicControl/
                └── main.cpp
```

Include the library in your application:

```cpp
#include <X9C104P.h>
```

## Constructor

The current project uses the following constructor pattern:

```cpp
X9C104P pot(3, 4, 5);
```

The arguments represent the INC, U/D, and CS control pins, respectively.

Confirm the argument order in `X9C104P.h` before using the library.

## Available Functions

The project documents the following public interface. Check `X9C104P.h` for the exact signatures.

| Function | Purpose |
|---|---|
| `begin()` | Initializes the control pins. |
| `home()` | Moves the wiper toward position 0. |
| `setPosition(position)` | Requests a wiper position from 0 to 99. |
| `setResistance(resistance)` | Converts a resistance request in ohms to a nominal position. |
| `getPosition()` | Returns the software-tracked position. |
| `getNominalResistance(position)` | Calculates nominal resistance for a position. |
| `resistanceToPosition(resistance)` | Converts a resistance request into a nominal position. |
| `getNominalTotalResistance()` | Returns the nominal total resistance used in calculations. |

## Example

```cpp
#include <Arduino.h>
#include <X9C104P.h>

X9C104P pot(3, 4, 5);

void setup() {
    Serial.begin(9600);

    pot.begin();
    pot.home();

    pot.setPosition(25);
    Serial.println(pot.getPosition());

    pot.setPosition(50);
    Serial.println(pot.getPosition());
}

void loop() {
}
```

This example illustrates the intended usage. Compile it against the actual library version before distributing it.

## Resistance Estimation

For a nominal 100 kΩ device, the simplified position-to-resistance relationship is:

\[
R_{\text{nominal}} = \frac{p}{99}\times100000\ \Omega
\]

where \(p\) is the requested wiper position from 0 to 99.

This relationship is a nominal estimate. It does not compensate for actual resistance tolerance or directly measure the physical resistance.

## Hardware Considerations

- Follow the X9C104P datasheet for supply and terminal-voltage requirements.
- Ensure that the control signals are compatible with the device.
- Use a suitable circuit for the intended load.
- Remember that the software tracker does not independently verify the physical wiper position.

## Example Application

The `examples/basicControl/` directory contains the project's basic control example.

The root project's `src/main.cpp` provides the main PlatformIO application used for building and testing the project.

## License

See the repository's `LICENSE` file for applicable licensing terms.