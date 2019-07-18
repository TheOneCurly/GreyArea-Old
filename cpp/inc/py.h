#ifndef PY_H
#define PY_H

#include <thread>
#include <pybind11/pybind11.h>

#include "data.h"
#include "control.h"

class Py {
public:
    static void Init();
    static void Stop();

private:
    static Control TemperatureController;
    static std::thread* ControlThread;
};

#endif // PY_H
