# GreyArea
Configuration files, control software, and web based user interface for a home sous-vide imersion cooker. Configuration files and paths assume this will be running on Raspbian, with minor changes any Linux distro will work. 


## Dependencies
+ Python3
  + Flask-SocketIO
+ PyBind11 <https://github.com/pybind/pybind11>

## Hardware
+ Raspberry Pi Zero (running Raspbian)
+ SRD-05VDC-SL-C Relay
+ DS18B20 One-wire temperature sensor

## Software Setup
### Automatic (Raspbian)
This is a work in progress, the setup script is not complete.
1. Clone this repository to the pi user's home folder (`/home/pi`).
2. Run `./setup.sh`
  This will automatically download python, python modules, nginx, supervisor, and pybind11, build the program (this may take a while on the zero), and start the service.
3. Go to the pi's IP address in a web browser and the control page should load.
### Manual (Advanced)
1. Clone the repository.
2. Clone PyBind11 to `./cpp`
3. Make sure all other dependencies are installed. Virtual wrappers are recommended.
4. Build the control program in `./cpp`
  + `cd ./cpp/build`
  + `cmake ..`
  + `make`
5. Run `./www/greyarea/app.py`
  + The web interface will available on port 5000
  
The defualt configuration uses Gunicorn to serve the flask application, Nginx to reverse proxy, and Supervisor to kick off and watchdog Gunicorn. None of that is strictly necessary as you can run the python command on boot and access the web interface over port 5000, but it does make it a little easier to use.

# Hardware Setup

# License
[MIT](LICENSE)
