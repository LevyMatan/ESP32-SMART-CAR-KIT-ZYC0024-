# ESP32CAM - 4x4 Car Project

## What this project is about?

Mostly it is about learning and having fun. I wanted to learn how to use ESP32CAM and how to control a car with it.  

The Project is based on the ESP32CAM and the ESP32CAM Car Kit.  

## Getting Started

### Prerequisites

1) You will need and ESP32CAM and the ESP32CAM Car Kit.
You can ask me for links to the products I used. or just search the web, there are plenty.

2) Arduino IDE - I used version 1.8.13

3) Install ESP32CAM library using the Arduino Library Manager

### Burn the code to the ESP32CAM

- Open the main file: ESP32CAM_Car.ino with the Arduino IDE.
- Connect the ESP32CAM to your computer.
- Select the correct board (Mine was ESP32 Wrover Module) and port in the Arduino IDE.
- Burn the code to the ESP32CAM.

## Code Tour

The code can be roughtly divided into three parts:

1. The "Car" code - provides the basic functionality for the operating the motors.
2. The Remote Controller code - an HTML based remote controller for the car.
3. The Webserver code - The remote controller webpage is hosted and servered by the ESP32CAM, which enables it to be accessed from any device in the same network.

Here is a quick overview of the files and folders:

- README.md
- ESP32CAM_Car.ino
- src
  - move
    - L298N.cpp
    - L298N.h
    - move.cpp
    - move.hpp
  - webserver
    - app_httpd.cpp
    - camera_index.h
    - html_string.cpp
    - joysticks.html
- tools
  - __init__.py
  - html_comprresser.py
  - html_to_c_variable.py
  - string_to_c_style_string.py
  