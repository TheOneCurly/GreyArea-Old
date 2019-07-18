#!/bin/bash

# Detect System

# Set Kernel Modules
ln -s /home/pi/config/etc/modules /etc/modules

# Install Nginx
apt -y install nginx

# Link nginx configuration
ln -s /home/pi/config/etc/nginx/nginx.conf /etc/nginx/nginx.conf
ln -s /home/pi/config/etc/nginx/sites-available/greyarea /etc/nginx/sites-available/greyarea

# Install Supervisor
apt -y install supervisor

# Link supervisor configuration
ln -s /home/pi/config/etc/supervisor/conf.d/greyarea.conf /etc/supervisor/conf.d/greyarea.conf
