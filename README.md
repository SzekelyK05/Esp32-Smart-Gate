# Esp32-Smart-Gate
Parking lot gate simulation using Esp32

## Bill of Materials
The project needs an esp32 (ESP32-C3 seeed studio), 2 HC-SR04 ultrasonic sensors, SG90 Micro Servo, 16x2 LCD display with I2C interface, breadboard and jumper wires.
Other Esp32 variants are compatible too, but the pins may be different.
No soldering needed.


## Wiring

Ultrasonic sensor In:   Vcc -> VIN/VBUS
                        Trig -> Pin 3
                        Echo -> Pin 4
                        Gnd -> Gnd

Ultrasonic sensor Out:  Vcc -> VIN/VBUS
                        Trig -> Pin 5
                        Echo -> Pin 21
                        Gnd -> Gnd

Lcd Display:            Gnd -> Gnd
                        Vcc -> VIN/VBUS
                        SDA -> Pin 6
                        SCL -> Pin 7

Micro Servo:            Brown wire -> Gnd
                        Red wire -> VIN/VBUS
                        Yellow wire -> Pin 2

## Dependencies
LiquidCrystal_I2C.h
ESP32Servo.h

## User guide
One ultrasonic sensor detects if a car is entering and reduces the number of available spaces in the parking lot (initially 5).
Another ultrasonic sensor detects if a car is leaving and increments the number of remaining parking spots.
In both cases the servo raises up the bar and stays open until the car has passed.

# Code features
The logic is based on a simple state machine (states: closed, open).
A function (checkUltrasonic) returns either true or false if an object has been detected.

## Installation

### Prerequisites
1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install the ESP32 board package in the Arduino IDE (follow [Espressif's official guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) if you haven't done this before).

### Setup Steps
1. **Clone the repository:**
   ```bash
   git clone (https://github.com/SzekelyK05/Esp32-Smart-Gate.git)

(Or download the repository as a ZIP file and extract it).
2. Open the sketch: Open the src/main.ino file in the Arduino IDE.

Configure your board:

Go to Tools > Board and select XIAO_ESP32C3 (or your specific ESP32 variant).

Go to Tools > Port and select the USB port your ESP32 is connected to.

Flash the firmware: Click the Upload button to compile and push the code to your board.