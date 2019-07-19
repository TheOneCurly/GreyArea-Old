#!/bin/bash

# Check for sudo
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

# Set Kernel Modules
ln -s /home/pi/config/etc/modules /etc/modules

# Install Python
dpkg -s python3 &> /dev/null
retVal = $?
if [ $? -eq 1 ]
then
    apt -y install python3
fi

# Install Nginx
dpkg -s nginx &> /dev/null
retVal = $?
if [ $? -eq 1 ]
then
    apt -y install nginx
fi

# Link nginx configuration
ln -s /home/pi/config/etc/nginx/nginx.conf /etc/nginx/nginx.conf
ln -s /home/pi/config/etc/nginx/sites-available/greyarea /etc/nginx/sites-available/greyarea

# Install Supervisor
dpkg -s supervisor &> /dev/null
retVal = $?
if [ $? -eq 1 ]
then
    apt -y install supervisor
fi

# Link supervisor configuration
ln -s /home/pi/config/etc/supervisor/conf.d/greyarea.conf /etc/supervisor/conf.d/greyarea.conf
