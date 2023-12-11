#!/bin/bash
g++ GPIO.cpp pushButton.cpp -o pushButton -pthread -lpaho-mqtt3c
config-pin -q p8.16
config-pin p8.16 gpio_pu
config-pin -q p8.16
