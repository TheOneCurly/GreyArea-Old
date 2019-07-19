#include "data.h"

std::atomic_bool Data::RelayState(true);
std::atomic<float> Data::CurrentTemperature(0);
std::atomic_bool Data::Enabled(true);
std::atomic<float> Data::CurrentSetpoint(0);

void Data::SetRelayState(bool relayState){
    RelayState = relayState;
}

bool Data::GetRelayState(){
    return RelayState;
}

void Data::SetCurrentTemperature(float currentTemperature){
    CurrentTemperature = currentTemperature;
}

float Data::GetCurrentTemperature(){
    return CurrentTemperature;
}

void Data::SetEnabled(bool enabled){
    Enabled = enabled;
}

bool Data::GetEnabled(){
    return Enabled;
}

void Data::SetCurrentSetpoint(float currentSetpoint){
    CurrentSetpoint = currentSetpoint;
}

float Data::GetCurrentSetpoint(){
    return CurrentSetpoint;
}

