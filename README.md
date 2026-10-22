# X9C104P Digital Potentiometer Project

A reusable Arduino C++ library and PlatformIO project for controlling the X9C104P digital potentiometer.

This project demonstrates digital potentiometer initialization, wiper positioning, nominal resistance conversion, and hardware testing using an Arduino Uno.

## Overview

The X9C104P is a digitally controlled potentiometer with a nominal end-to-end resistance of 100 kΩ. Its wiper position is controlled through digital control signals rather than a mechanical adjustment knob.

This project provides a reusable C++ interface for controlling the device and an example application for testing its operation.

The library is designed to simplify common operations, including initializing the control pins, homing the wiper, selecting a wiper position, and calculating nominal resistance values.

## Features

- Reusable Arduino C++ library.
- X9C104P initialization and control.
- Wiper position control from 0 to 99.
- Wiper homing.
- Software-based position tracking.
- Nominal resistance-to-position conversion.
- Position-to-nominal-resistance calculation.
- PlatformIO project integration.
- Example application for hardware testing.

## Hardware Requirements

- Arduino Uno or a compatible Arduino board.
- X9C104P digital potentiometer.
- Breadboard and jumper wires.
- USB cable for programming the Arduino.
- Multimeter for measuring the wiper voltage.

Additional components may be required depending on the circuit in which the digital potentiometer is used.

## Hardware Connections

The example configuration uses Arduino Uno digital pins D3, D4, and D5 to control the X9C104P.

| X9C104P Pin | Signal | Connection |
|---|---|---|
| 1 | INC | Arduino D3 |
| 2 | U/D | Arduino D4 |
| 3 | RH | Application-dependent; connect to 5 V for the documented voltage-sweep test |
| 4 | VSS | GND |
| 5 | RW | Wiper output; connect to a multimeter or Arduino A0 for measurement |
| 6 | RL | Application-dependent; connect to GND for the documented voltage-sweep test |
| 7 | CS | Arduino D5 |
| 8 | VCC | Supply voltage permitted by the datasheet |

For the voltage-sweep demonstration, RH is connected to 5 V and RL to GND. The wiper voltage is measured between RW and GND.

**Hardware safety:** Verify the supply-voltage, terminal-voltage, and control-input requirements in the X9C104P datasheet before connecting the device. Do not assume that the potentiometer can safely handle arbitrary voltages or currents.

## Project Structure

```text
X9C104P-Digital-POT-Project/
├── README.md
├── LICENSE
├── .gitignore
├── platformio.ini
├── include/
│   └── README.md
├── lib/
│   └── X9C104P/
│       ├── library.json
│       ├── README.md
│       ├── src/
│       │   ├── X9C104P.h
│       │   └── X9C104P.cpp
│       └── examples/
│           └── basicControl/
│               └── main.cpp
├── src/
│   └── main.cpp
└── test/
    └── README.md
```

## Software Requirements

- Visual Studio Code.
- PlatformIO IDE extension.
- Git for version control.
- Arduino framework supported by the selected PlatformIO board configuration.

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/X9C104P-Digital-POT-Project.git
```

Replace `YOUR_USERNAME` with the repository owner's GitHub username.

### 2. Open the project

Open the cloned project directory in Visual Studio Code and allow PlatformIO to initialize the project.

### 3. Connect the hardware

Connect the Arduino Uno and X9C104P using the wiring table above.

Check the wiring and supply voltage before applying power.

### 4. Build the project

Use the PlatformIO **Build** command or run:

```bash
pio run
```

### 5. Upload the application

Connect the Arduino Uno and run:

```bash
pio run --target upload
```

If PlatformIO cannot identify the correct serial port, configure the upload port in `platformio.ini`.

## Basic Usage

The library can be included in an Arduino application with:

```cpp
#include <X9C104P.h>
```

The following example illustrates the intended interface:

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

    pot.setPosition(0);
    Serial.println(pot.getPosition());
}

void loop() {
}
```

This example assumes the constructor accepts the INC, U/D, and CS pins in that order. Confirm that the function names and behavior match the version of the library included in this repository.

## Testing and Observed Results

The project has been tested with an Arduino Uno and an X9C104P digital potentiometer.

The position-control test performs the following sequence:

1. Home the wiper to position 0.
2. Move the wiper to position 25.
3. Move the wiper to position 50.
4. Return the wiper to position 0.

During the reported voltage-sweep test, the following approximate wiper voltages were observed:

| Wiper Position | Observed Wiper Voltage |
|---:|---:|
| 25 | Approximately 1.3 V |
| 50 | Approximately 2.6 V |
| 0 | Approximately 0 V |

These values are observations from the tested circuit, not guaranteed output values for all hardware configurations.

## Resistance Calculation

For a nominal 100 kΩ device, the library can estimate the nominal resistance associated with a wiper position using:

\[
R_{\text{nominal}} \approx \frac{p}{99}\times100000\ \Omega
\]

where \(p\) is the wiper position from 0 to 99.

For example, position 50 corresponds to approximately 50.51 kΩ in this simplified nominal model.

**Important:** The library calculates an estimated resistance from the requested position. It does not directly measure resistance. Actual resistance depends on device tolerance, wiper resistance, and the terminals used.

## Limitations

- Resistance values are nominal calculations, not direct measurements.
- The actual end-to-end resistance can differ from 100 kΩ.
- Position 0 does not guarantee exactly 0 Ω between the wiper and an endpoint.
- The software position tracker assumes that the physical wiper follows the library's commands.
- External changes to the wiper position can make the software tracker inaccurate.
- The permitted terminal voltages and currents depend on the device's specifications and circuit configuration.

## Future Improvements

Potential improvements include:

- Serial Monitor commands for setting resistance.
- Additional Arduino board examples.
- Automated tests for resistance-to-position calculations.
- Expanded hardware test documentation.
- A wiring diagram and photographs of the tested hardware.



## Author

Developed as an embedded systems project using Arduino and PlatformIO.