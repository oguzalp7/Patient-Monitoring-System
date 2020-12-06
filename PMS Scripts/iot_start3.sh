#!/bin/bash
gnome-terminal -e ./iot_start4.sh
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0