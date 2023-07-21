# ASHER Documentation

## Description
Automated Synchronized High-Stability Electronic Rudder, (ASHER) is an Automated Rudder System designed for creating automatic rudder movement using a PID controller while an RC aircraft is flying. 

* The original project's goal was to actually test the system in an RC aircraft, however, we did not recieve any of our part to build it in time so we had to create all the systems ourselves with makeshift parts found around our engineering shop.

ASHER is a system that consists of two distinct sections with different purposes. The first section is responsible for digitalizing the output of an inclinometer using an infrared sensor array connected to a microcontroller. The second section is the PID (Proportional-Integral-Derivative) system, which utilizes the input from the sensor system and controls a servo motor that adjusts the rudder. ASHER is designed to maintain stability and control in a certain application.

## Sensor System
The sensor system in ASHER consists of an infrared sensor array and an inclinometer. The infrared sensor array is positioned in front of the inclinometer, aligned with the centerline of a glass tube containing a black ball. The purpose of the infrared sensors is to detect the position of the black ball inside the tube. The sensor array includes multiple infrared sensors arranged in parallel. The electrical input is shared among all the sensors, but each sensor has its corresponding output connected to a microcontroller.

Each infrared sensor in the array provides a digital output, indicating either a HIGH or LOW reading. The microcontroller used in the system should have at least 30 input pins to accommodate the sensor array. The array's output is represented as a numerical value, where the sensor number corresponds to the index in the array, and the output value represents the detected position of the black ball.

## PID System
The PID system in ASHER is responsible for processing the input from the sensor system and generating control signals for the servo motor that controls the rudder. The PID system helps maintain stability by continuously adjusting the rudder position based on the feedback from the sensor system.

The PID system is implemented using a PID controller class named PIDSys. The constructor of this class takes several parameters, including the sampling time (dt), maximum and minimum position limits (maxpos and minpos), maximum and minimum output limits (maxout and minout), and the PID gains (Kp, Ki, and Kd).

The PID controller calculates the control signal by executing the calculatePID() function. This function reads the sensor values from the microcontroller's input pins, determines the PID error based on the sensor readings, and performs the PID calculations using the proportional, integral, and derivative terms. The output signal is then constrained within the defined output limits.

## Usage

To use the ASHER system, follow these steps:

Set up the hardware components, including the infrared sensor array, the inclinometer with the black ball, the microcontroller, and the servo motor connected to the rudder.

Connect the infrared sensor array to the microcontroller's input pins, making sure the electrical connections are correct.

Upload the provided code to the microcontroller using the Arduino IDE or compatible software.

Open the Serial monitor to observe the position values printed by the system.

Verify that the ASHER system is functioning properly by observing the servo motor's movement and the stability of the position values reported in the Serial monitor.

Note: Adjust the PID controller parameters (Kp, Ki, and Kd) in the PIDSys constructor according to the specific requirements and characteristics of your application.
