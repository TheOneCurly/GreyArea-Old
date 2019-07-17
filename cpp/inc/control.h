#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <string>
#include <unistd.h>

#include "gpio.h"
#include "ds18b20.h"
#include "data.h"

class Control{
public:
    union {
        float asFloat;
        uint32_t asInt;
    } Converter;

    Control(int relayPin);
    void run();

private:
    static const int16_t P = 40;
    static const int16_t I = 10;
    static const int16_t D = 0;

    int m_relayPin;
    std::string m_sensorID;

    GPIO m_gpio;
    DS18B20 m_sensor;

    void openRelay();
    void closeRelay();
};

#endif // CONTROL_H
