#ifndef LINEAR_POT_H
#define LINEAR_POT_H

#include <Arduino.h>
#include "Sensor.h"

class LinearPot : public Sensor {

private:
    static constexpr uint16_t NUM_READINGS = 5;
    static constexpr uint16_t MIN_RANGE = 10;
    static constexpr uint16_t MAX_RANGE = 400; // Max range in mm

    int16_t readIdx;
    int16_t sum;
    int16_t readings[NUM_READINGS];

public:
    LinearPot() : readIdx(0), sum(0) {
        memset(readings, 0, sizeof(readings));
    }

    int16_t calculate() override {
        int16_t dist = map(analogRead(pin), 0, 1023, MIN_RANGE, MAX_RANGE);
        sum = sum - readings[readIdx];
        readings[readIdx] = dist;
        sum = sum + dist;
        readIdx = (readIdx + 1) % NUM_READINGS;
        int16_t avg = sum / NUM_READINGS;
        return avg; // Moving average of Displacement in mm
    }
};

#endif
