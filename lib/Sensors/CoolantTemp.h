#ifndef COOLANT_TEMP_H
#define COOLANT_TEMP_H

#include <Arduino.h>
#include "Sensor.h"

// Stienhart Equation Constants, see matlab file to adjust
#define A 0.000689287402357408
#define B 0.000289807635936112
#define C -0.0000000158833675

#define RESISTOR_VAL 10030.0

class CoolantTemp : public Sensor {

private:
    float voltage;
    float resistance;
    float tempC;

public:
    CoolantTemp() : voltage(0), resistance(0), tempC(0) {}

    void calculate() override {
        voltage = analogRead(pin) * (5.0 / 1023.0);
        resistance = voltage * RESISTOR_VAL / (5.00 - voltage);
        tempC = pow((A + B * log(resistance) + C * pow(log(resistance), 3)), -1) - 273.15;

        tx(&tempC, sizeof(tempC));
    }
};

#endif
