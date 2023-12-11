#!/bin/bash
g++ derek_LED.cpp textBox.cpp -o textBox -lpaho-mqtt3c
config-pin P9.12 gpio
