🏎️ F1 RC Car

A custom-built, 3D-printed remote-controlled racing car inspired by Formula 1.

This project was developed as a hands-on electronics, CAD, 3D printing and programming project. The goal was to design and build the car from scratch, including the chassis, wheels, steering system and aerodynamic parts, while learning how the different electronic and mechanical systems work together.

 Features:
Custom 3D-printed chassis
Formula 1-inspired body and aerodynamic design
Rear-wheel drive
Two DC geared motors
Servo-controlled front steering
Wireless remote control
Custom-designed wheels
Custom front wing and nose
Arduino-based electronics
LCD display on the controller
Accelerator and brake controls
Joystick-based steering
NRF24L01 wireless communication
Designed and modified using CAD software

 Electronics:
Car
Arduino UNO R4 WiFi
L298N motor driver
2× geared DC motors
20 kg metal gear steering servo
2× 18650 batteries
NRF24L01 PA+LNA wireless module
LM2596 buck converter
Controller
Arduino UNO R3
NRF24L01 PA+LNA wireless module
Joystick
16×2 I2C LCD
Accelerator button
Brake button

Wireless Control:

The car and controller communicate using NRF24L01 PA+LNA modules.

The controller sends the steering and driving commands wirelessly to the Arduino on the car. The NRF24L01 modules replaced the original 433 MHz RF system to provide a more reliable and capable communication system.

The communication uses the Arduino's hardware SPI interface.

 Software:

The project is programmed using Arduino/C++.

The software is divided into two main parts:

Controller:

The controller reads:

Joystick position
Accelerator button
Brake button

It then sends these values wirelessly to the car.

Car

The car receives the controller data and converts it into:

Motor direction and speed
Steering servo position

The L298N controls the two drive motors, while a servo controls the front steering.

 CAD & 3D Printing:

A large part of the project was designing the mechanical components myself.

The project includes CAD and 3D-printable files for components such as:

Chassis
Motor supports
Arduino supports
L298N support
Battery holder
Steering components
Steering linkage
Wheels
Front wing
Front nose
Other mounting components

Different versions of several parts were designed, printed and tested before reaching the final versions.

Design Process:

The car was developed iteratively rather than designing everything perfectly on the first attempt.

The general process was:

Initial F1-inspired concept
Chassis design
Design of electronic and motor mounts
3D printing and physical testing
Modification of parts that did not fit correctly
Steering mechanism development
Wheel and aerodynamic component design
Electronics assembly
Motor testing
Steering servo testing
Wireless communication development
Integration of the different systems

Testing and redesigning parts was an important part of the project.

 What I Learned

Through this project I learned about:

Arduino programming
Wireless communication
SPI communication
Motor drivers
DC motors
Servo motors
Voltage regulation
Battery-powered electronics
CAD design
3D printing
Mechanical prototyping
Iterative design
Troubleshooting electronics
Integrating hardware and software

One of the main lessons from the project was that designing a system is only part of the work. A large part of the process is testing, finding problems and redesigning the components until everything works together.

 Future Improvements

Possible future improvements include:

DRS system using an SG90 servo
Lights
Additional controller buttons
Improved bodywork
More aerodynamic components
Improved wireless communication
Additional telemetry
More advanced driving controls
 Project Status

The main car structure, steering, motors, controller and wireless communication systems have been developed and tested.

The project is currently considered a functional prototype, with additional features planned for future development.

Made as a learning project combining CAD, 3D printing, electronics and programming.
