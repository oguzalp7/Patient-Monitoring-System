#!/bin/bash
gnome-terminal -e ./iot_start5.sh
rosrun PMS serial_node2.py _port:=/dev/ttyUSB1