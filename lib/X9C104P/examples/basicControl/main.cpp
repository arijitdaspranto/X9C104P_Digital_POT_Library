#include <Arduino.h>
#include <X9C104P.h>

X9C104P pot(3, 4, 5);

void setup() {
    Serial.begin(9600);
    delay(500);

    Serial.println("X9C104P Library Test");

    pot.begin();

    Serial.println("Homing to position 0...");
    pot.home();

    Serial.print("Position: ");
    Serial.println(pot.getPosition());

    delay(1500);

    Serial.println("Moving to position 25...");
    pot.setPosition(25);
    Serial.println(pot.getPosition());

    delay(2000);

    Serial.println("Moving to position 50...");
    pot.setPosition(50);
    Serial.println(pot.getPosition());

    delay(2000);

     Serial.println("Moving to position 75...");
    pot.setPosition(75);
    Serial.println(pot.getPosition());

    delay(2000);

     Serial.println("Moving to position 100...");
    pot.setPosition(99);
    Serial.println(pot.getPosition());

    delay(2000);

    Serial.println("Returning to position 0...");
    pot.setPosition(0);
    Serial.println(pot.getPosition());

    Serial.println("Test complete.");
}

void loop() {
}