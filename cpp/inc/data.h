#ifndef DATA_H
#define DATA_H

#include <atomic>

class Data {
public:
    static void SetRelayState(bool relayState);
    static bool GetRelayState();

    static void SetCurrentTemperature(float currentTemperature);
    static float GetCurrentTemperature();

    static void SetEnabled(bool enabled);
    static bool GetEnabled();

    static void SetCurrentSetpoint(float currentSetpoint);
    static float GetCurrentSetpoint();

private:
    static std::atomic_bool RelayState;
    static std::atomic<float> CurrentTemperature;
    static std::atomic_bool Enabled;
    static std::atomic<float> CurrentSetpoint;
};

#endif // DATA_H
