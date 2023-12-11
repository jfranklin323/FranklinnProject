#!/bin/bash
g++ publishTemp.cpp AnalogIn.cpp -o publishTemp -lpaho-mqtt3c
g++ AnalogIn.cpp derek_LED.cpp subscribeTemp.cpp -o subscribeTemp -lpaho-mqtt3c
