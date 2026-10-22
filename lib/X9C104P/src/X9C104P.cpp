#include "X9C104P.h"

constexpr float X9C104P::NOMINAL_RESISTANCE;


// Constructor
X9C104P::X9C104P(
    uint8_t incPin,
    uint8_t udPin,
    uint8_t csPin
) :
    _incPin(incPin),
    _udPin(udPin),
    _csPin(csPin),
    _currentPosition(0)
{
}


// Initialize the control pins
void X9C104P::begin() {

    pinMode(_incPin, OUTPUT);
    pinMode(_udPin, OUTPUT);
    pinMode(_csPin, OUTPUT);

    digitalWrite(_incPin, HIGH);
    digitalWrite(_udPin, LOW);
    digitalWrite(_csPin, HIGH);

    delayMicroseconds(10);
}


// Generate one INC pulse
void X9C104P::pulseINC() {

    digitalWrite(_incPin, HIGH);
    delayMicroseconds(5);

    digitalWrite(_incPin, LOW);
    delayMicroseconds(5);

    digitalWrite(_incPin, HIGH);
    delayMicroseconds(5);
}


// Move a number of steps in a selected direction
void X9C104P::moveSteps(bool towardRH, int steps) {

    if (steps <= 0) {
        return;
    }

    // HIGH selects movement toward RH.
    // LOW selects movement toward RL.
    digitalWrite(_udPin, towardRH ? HIGH : LOW);

    delayMicroseconds(5);

    digitalWrite(_incPin, HIGH);
    digitalWrite(_csPin, LOW);

    delayMicroseconds(5);

    for (int i = 0; i < steps; i++) {
        pulseINC();
    }

    /*
      Leave INC LOW before raising CS.
      This requests termination without a
      nonvolatile-memory store.
    */
    digitalWrite(_incPin, LOW);
    delayMicroseconds(5);

    digitalWrite(_csPin, HIGH);

    delayMicroseconds(5);

    // Return INC to its idle state after deselection.
    digitalWrite(_incPin, HIGH);
}


// Home to the RL endpoint
void X9C104P::home() {

    digitalWrite(_csPin, HIGH);
    digitalWrite(_incPin, HIGH);

    digitalWrite(_udPin, LOW);

    delayMicroseconds(5);

    digitalWrite(_csPin, LOW);

    delayMicroseconds(5);

    // More pulses than needed to reach the endpoint.
    for (int i = 0; i < 100; i++) {
        pulseINC();
    }

    // End the operation without requesting a memory store.
    digitalWrite(_incPin, LOW);
    delayMicroseconds(5);

    digitalWrite(_csPin, HIGH);

    delayMicroseconds(5);

    digitalWrite(_incPin, HIGH);

    _currentPosition = MIN_POSITION;
}


// Set an absolute position
bool X9C104P::setPosition(int position) {

    if (position < MIN_POSITION ||
        position > MAX_POSITION) {
        return false;
    }

    if (position == _currentPosition) {
        return true;
    }

    bool towardRH = (position > _currentPosition);

    int steps = abs(position - _currentPosition);

    moveSteps(towardRH, steps);

    _currentPosition = position;

    return true;
}


// Convert resistance to position
int X9C104P::resistanceToPosition(
    float resistanceOhms
) const {

    if (resistanceOhms < 0.0f) {
        resistanceOhms = 0.0f;
    }

    if (resistanceOhms > NOMINAL_RESISTANCE) {
        resistanceOhms = NOMINAL_RESISTANCE;
    }

    int position = (int)(
        resistanceOhms * MAX_POSITION /
        NOMINAL_RESISTANCE + 0.5f
    );

    return constrain(position, MIN_POSITION, MAX_POSITION);
}


// Set resistance using the nominal resistance model
bool X9C104P::setResistance(float resistanceOhms) {

    int position = resistanceToPosition(resistanceOhms);

    return setPosition(position);
}


// Read the software-tracked position
int X9C104P::getPosition() const {

    return _currentPosition;
}


// Calculate nominal array resistance for a position
float X9C104P::getNominalResistance(int position) const {

    if (position < MIN_POSITION ||
        position > MAX_POSITION) {
        return -1.0f;
    }

    return NOMINAL_RESISTANCE *
           position / MAX_POSITION;
}


// Return nominal total resistance
float X9C104P::getNominalTotalResistance() const {

    return NOMINAL_RESISTANCE;
}