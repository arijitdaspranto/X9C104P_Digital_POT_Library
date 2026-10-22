#ifndef X9C104P_H
#define X9C104P_H

#include <Arduino.h>

class X9C104P {
public:

    // Constructor: specify the Arduino pins.
    X9C104P(uint8_t incPin, uint8_t udPin, uint8_t csPin);

    // Initialize the GPIO pins.
    void begin();

    // Move to the minimum RW-RL resistance endpoint.
    void home();

    // Move to a particular position: 0 to 99.
    bool setPosition(int position);

    // Convert a nominal resistance request into a position.
    bool setResistance(float resistanceOhms);

    // Return the software-tracked position.
    int getPosition() const;

    // Calculate nominal resistance at a given position.
    float getNominalResistance(int position) const;

    // Convert nominal resistance to a position.
    int resistanceToPosition(float resistanceOhms) const;

    // Return the nominal total resistance.
    float getNominalTotalResistance() const;


private:

    uint8_t _incPin;
    uint8_t _udPin;
    uint8_t _csPin;

    int _currentPosition;

    static const int MIN_POSITION = 0;
    static const int MAX_POSITION = 99;

    static constexpr float NOMINAL_RESISTANCE = 100000.0f;

    // Generate one increment/decrement pulse.
    void pulseINC();

    // Move by a specified number of steps.
    void moveSteps(bool towardRH, int steps);
};

#endif