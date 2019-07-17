#include "gpio.h"

const std::string GPIO::GPIOPath = "/sys/class/gpio";
const std::string GPIO::ExportPath = "/export";
const std::string GPIO::DirectionPath = "/direction";
const std::string GPIO::ValuePath = "/value";
const std::string GPIO::UnexportPath = "/unexport";

const std::string GPIO::DirectionOut = "out";
const std::string GPIO::DirectionIn = "in";
const std::string GPIO::StateHigh = "1";
const std::string GPIO::StateLow = "0";

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
        std::ofstream registerStream;
        registerStream.open((GPIOPath + ExportPath).c_str());
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
        std::ofstream stateStream;
        stateStream.open((GPIOPath + getDirFromPin(pin) + ValuePath).c_str());
        if(state == High){
            stateStream << StateHigh;
        }else{
            stateStream << StateLow;
        }
        stateStream.close();

//        sleep(1);

    }else{
        std::cout << "Pin " << pin << " is not registered" << std::endl;
    }
}

GPIO::State GPIO::getState(unsigned int pin){
    State state = Low;
    if(isRegistered(pin)){
        std::ifstream stateStream;
        stateStream.open((GPIOPath + getDirFromPin(pin) + ValuePath).c_str());

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
        std::ofstream unregisterStream;
        unregisterStream.open((GPIOPath + UnexportPath).c_str());
        unregisterStream << pin;
        unregisterStream.close();

        m_registeredPins[pin] = 0;
    }
}

void GPIO::setDirection(int pin, GPIO::Direction direction){
    std::ofstream directionStream;
    directionStream.open((GPIOPath + getDirFromPin(pin) + DirectionPath).c_str());
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
