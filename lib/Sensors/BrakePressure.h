#ifndef BRAKE_PRESSURE_H
#define BRAKE_PRESSURE_H

#include <Arduino.h>
#include "Sensor.h"

class BrakePressure : public Sensor {

private:
    static constexpr uint16_t MIN_MV = 500; // Voltage cutoff in mV
    static constexpr uint16_t MAX_MV = 4500;
    static constexpr uint16_t MIN_PSI = 0;
    static constexpr uint16_t MAX_PSI = 3000;

public:
    BrakePressure() {};
    
    int16_t calculate() override {
        int16_t mV = analogRead(pin) * 5000 / 1023;
        int16_t psi = map(mV, MIN_MV, MAX_MV, MIN_PSI, MAX_PSI);

        return psi;  // Pressure in PSI × 10
    }
};

#endif
