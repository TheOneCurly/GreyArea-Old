#include "py.h"

#define debug std::cout << "Py: "

Control Py::TemperatureController(17);
std::thread* Py::ControlThread = nullptr;

Py::Py(){
    debug << "Creating a Py" << std::endl;
}

void Py::Init(){
    if(ControlThread == nullptr){
        ControlThread = new std::thread(&Control::run, &TemperatureController);
    }
}

void Py::Stop(){
    if(ControlThread != nullptr){
        ControlThread->join();
    }
}

PYBIND11_MODULE(SousVide, m) {
    pybind11::class_<Py>(m, "Py")
        .def(pybind11::init<>())
        .def_static("Init", &Py::Init)
        .def_static("Stop", &Py::Stop);

    pybind11::class_<Data>(m, "Data")
        .def(pybind11::init<>())
        .def_static("SetRelayState", &Data::SetRelayState)
        .def_static("GetRelayState", &Data::GetRelayState)
        .def_static("SetCurrentTemperature", &Data::SetCurrentTemperature)
        .def_static("GetCurrentTemperature", &Data::GetCurrentTemperature)
        .def_static("SetEnabled", &Data::SetEnabled)
        .def_static("GetEnabled", &Data::GetEnabled)
        .def_static("SetCurrentSetpoint", &Data::SetCurrentSetpoint)
        .def_static("GetCurrentSetpoint", &Data::GetCurrentSetpoint);
}
