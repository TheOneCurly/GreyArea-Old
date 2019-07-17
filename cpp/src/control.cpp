#include "control.h"

Control::Control(int relayPin) : m_relayPin(relayPin){
    m_gpio.registerGPIO(m_relayPin);
    m_gpio.setDirection(m_relayPin, GPIO::Out);

    m_sensorID = m_sensor.discover();
}

void Control::run(){
    // Control Variables
    float currentSetpoint = 0.f;
    float currentError = 0.f;
    float currentTemp = 0.f;

    float lastError = 0.f;
    float errorIntegral = 0.f;
    float errorDerivative = 0.f;

    float pidResult = 0.f;

    // Start with relay open
    openRelay();

    while(true){
        if(Data::GetEnabled()){
            // Get current setpoint
            Converter.asInt = Data::GetCurrentSetpoint();
            currentSetpoint = Converter.asFloat;

            // Read current temperature
            currentTemp = m_sensor.read(m_sensorID);
            Converter.asFloat = currentTemp;
            Data::SetCurrentTemperature(Converter.asInt);

            // Calculate P
            currentError = currentSetpoint - currentTemp;

            // Sum and cap I
            errorIntegral += currentError;;
            if(errorIntegral > 50){
                errorIntegral = 50;
            }else if(errorIntegral < -50){
                errorIntegral = -50;
            }

            // Calculate D
            errorDerivative = currentError - lastError;

            // Calculate and cap PID
            pidResult = (P * currentError) + (I * errorIntegral) + (D * errorDerivative);
            if(pidResult > 500){
                pidResult = 500;
            }else if(pidResult < -500){
                pidResult = -500;
            }

            // Set relay
            if(pidResult > 0){
                closeRelay();
            }else{
                openRelay();
            }
        }

        sleep(1);
    }
}

void Control::openRelay(){
    m_gpio.setState(m_relayPin, GPIO::Low);
    Data::SetRelayState(false);
}

void Control::closeRelay(){
    m_gpio.setState(m_relayPin, GPIO::High);
    Data::SetRelayState(true);
}
