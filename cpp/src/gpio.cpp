#include "gpio.h"

#define debug std::cout << "GPIO: "

GPIO::GPIO() : m_registeredPins(MaxGPIO, 0){}

GPIO::~GPIO(){
    // Unregister all registered GPIO
    for(unsigned int i = 0; i < MaxGPIO; i++){
        if(m_registeredPins[i] != 0){
            unregister(i);
        }
    }
}

bool GPIO::registerGPIO(unsigned int pin){
    bool ok = false;

    if(pin < MaxGPIO){
        std::string path(GPIOPath);
        path.append(ExportPath);
        std::ofstream registerStream;
        registerStream.open(path);
        registerStream << pin;
        registerStream.close();

        // ToDo: replace with spin that looks for the gpio's directory
        sleep(1);

        m_registeredPins[pin] = 1;
        ok = true;
    }

    return ok;
}

void GPIO::setState(unsigned int pin, GPIO::State state){
    if(isRegistered(pin)){
        std::string path(GPIOPath);
        path.append(getDirFromPin(pin));
        path.append(ValuePath);

        std::ofstream stateStream;
        stateStream.open((path));
        if(state == High){
            stateStream << StateHigh;
        }else{
            stateStream << StateLow;
        }
        stateStream.close();
    }
}

GPIO::State GPIO::getState(unsigned int pin){
    State state = Low;
    if(isRegistered(pin)){
        std::string path(GPIOPath);
        path.append(getDirFromPin(pin));
        path.append(ValuePath);

        std::ifstream stateStream;
        stateStream.open(path);

        std::string stateString;
        stateStream >> stateString;

        stateStream.close();

        if(stateString.compare("1") == 0){
            state = High;
        }else{
            state = Low;
        }
    }

    return state;
}

bool GPIO::isRegistered(unsigned int pin){
    return (m_registeredPins[pin] == 1);
}

void GPIO::unregister(unsigned int pin){
    if(pin < MaxGPIO){
        std::string path(GPIOPath);
        path.append(UnexportPath);

        std::ofstream unregisterStream;
        unregisterStream.open(path);
        unregisterStream << pin;
        unregisterStream.close();

        m_registeredPins[pin] = 0;
    }
}

void GPIO::setDirection(int pin, GPIO::Direction direction){
    std::string path(GPIOPath);
    path.append(getDirFromPin(pin));
    path.append(DirectionPath);

    std::ofstream directionStream;
    directionStream.open(path);
    if(direction == In){
        directionStream << DirectionIn;
    }else{
        directionStream << DirectionOut;
    }
    directionStream.close();
}

std::string GPIO::getDirFromPin(int pin){
    std::ostringstream dir;
    dir << "/gpio" << pin;
    return dir.str();
}
