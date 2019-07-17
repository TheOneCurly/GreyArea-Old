#ifndef DATA_H
#define DATA_H

#include <atomic>

class Data {
public:
    static void SetRelayState(bool relayState);
    static bool GetRelayState();

    static void SetCurrentTemperature(int currentTemperature);
    static int GetCurrentTemperature();

    static void SetEnabled(bool enabled);
    static bool GetEnabled();

    static void SetCurrentSetpoint(int currentSetpoint);
    static int GetCurrentSetpoint();

private:
    static std::atomic_bool RelayState;
    static std::atomic_int CurrentTemperature;
    static std::atomic_bool Enabled;
    static std::atomic_int CurrentSetpoint;
};

#endif // DATA_H
