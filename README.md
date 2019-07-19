# GreyArea
Configuration files, control software, and web based user interface for a home sous-vide imersion cooker. Configuration files and paths assume this will be running on Raspbian, with minor changes any Linux distro will work. 

## Dependencies
+ Nginx
+ Supervisor
+ Python3
+ Flask
+ PyBind11 <https://github.com/pybind/pybind11>

## Setup Instructions
For Raspbian.
1. Clone this repository to the pi user's home folder (/home/pi).
2. Run `./setup.sh`
  This will automatically download python, python modules, nginx, supervisor, and pybind11, build the program (this may take a while on the zero), and start the service.
