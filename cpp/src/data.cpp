#include "data.h"

std::atomic_bool Data::RelayState(true);
std::atomic_int Data::CurrentTemperature(0);
std::atomic_bool Data::Enabled(true);
std::atomic_int Data::CurrentSetpoint(0);

void Data::SetRelayState(bool relayState){
    RelayState = relayState;
}

bool Data::GetRelayState(){
    return RelayState;
}

void Data::SetCurrentTemperature(int currentTemperature){
    CurrentTemperature = currentTemperature;
}

int Data::GetCurrentTemperature(){
    return CurrentTemperature;
}

void Data::SetEnabled(bool enabled){
    Enabled = enabled;
}

bool Data::GetEnabled(){
    return Enabled;
}

void Data::SetCurrentSetpoint(int currentSetpoint){
    CurrentSetpoint = currentSetpoint;
}

int Data::GetCurrentSetpoint(){
    return CurrentSetpoint;
}

