#ifndef GPIO_H
#define GPIO_H

#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <errno.h>
#include <unistd.h>

///
/// \brief The GPIO class provides an interface to the Raspberry PI GPIO pins
/// http://www.hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html
///
class GPIO{
public:
    enum Direction{
        In,
        Out
    };
    
    enum State{
        Low,
        High
    };

    GPIO();
    ~GPIO();
    
    ///
    /// \brief registerGPIO - Export a pin, must be called before a pin is used
    /// \param pin - Pin number
    /// \return Success
    ///
    bool registerGPIO(unsigned int pin);

    ///
    /// \brief unregister - Unexport a pin
    /// \param pin - Pin number
    ///
    void unregister(unsigned int pin);

    ///
    /// \brief setDirection - Set the In/Out direction of a pin
    /// \param pin - Pin number
    /// \param direction
    ///
    void setDirection(int pin, Direction direction);

    ///
    /// \brief setState - Set the value of a pin
    /// \param pin - Pin number
    /// \param state
    ///
    void setState(unsigned int pin, State state);

    ///
    /// \brief getState - Get the current state of a pin
    /// \param pin - Pin number
    /// \return
    ///
    State getState(unsigned int pin);

    ///
    /// \brief isRegistered - Check if a pin has been registered
    /// \param pin - Pin number
    /// \return
    ///
    bool isRegistered(unsigned int pin);

private:
    static const unsigned int MaxGPIO = 40;

    static const std::string GPIOPath;
    static const std::string ExportPath;
    static const std::string DirectionPath;
    static const std::string ValuePath;
    static const std::string UnexportPath;

    static const std::string DirectionOut;
    static const std::string DirectionIn;

    static const std::string StateHigh;
    static const std::string StateLow;

    std::string getDirFromPin(int pin);

    std::vector<int> m_registeredPins;
};

#endif // GPIO_H
