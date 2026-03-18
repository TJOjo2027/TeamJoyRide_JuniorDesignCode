cmake_minimum_required(VERSION 3.29)
project(Junior_Design___Systems_Engineering)

set(CMAKE_CXX_STANDARD 20)

include_directories("C:/Users/tojo/AppData/Local/Arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino")

add_executable(Junior_Design___Systems_Engineering main.cpp
        IRSensor.h)
