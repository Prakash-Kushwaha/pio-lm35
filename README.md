# LM35 Temperature Display with ATmega32 and 16x2 I2C LCD

This project uses an ATmega32 microcontroller to read temperature data from an LM35 temperature sensor and displays it on a 16x2 LCD using the I2C protocol. The temperature readings update dynamically on the LCD, refreshing only when there is a significant change.

## Table of Contents
- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Setup and Installation](#setup-and-installation)
- [Code Explanation](#code-explanation)
- [Custom Character for Degree Symbol](#custom-character-for-degree-symbol)
- [Usage](#usage)
- [License](#license)

## Overview
The LM35 sensor is an analog temperature sensor that outputs a voltage linearly proportional to temperature. Using the ATmega32's ADC, this voltage is read and converted into temperature in Celsius. The reading is then displayed on a 16x2 I2C LCD. This project demonstrates using analog-to-digital conversion with ATmega32 and an I2C LCD interface for compact temperature monitoring.

## Hardware Requirements
- ATmega32 Microcontroller
- LM35 Temperature Sensor
- 16x2 LCD with I2C Module
- Breadboard and jumper wires
- External 5V power supply (optional)

## Circuit Diagram
The connections for this project are as follows:
- **LM35 sensor**
  - VCC to +5V
  - GND to Ground
  - Output (Vout) to ATmega32 ADC channel (PA0)

- **16x2 I2C LCD**
  - SDA to ATmega32 SDA
  - SCL to ATmega32 SCL
  - VCC to +5V
  - GND to Ground

## Setup and Installation
1. **Software Setup**: Ensure you have the Arduino IDE with the ATmega32 board library and the necessary LCD I2C libraries installed.
2. **Hardware Setup**: Assemble the circuit as per the circuit diagram.
3. **Code Upload**: Connect the ATmega32 to your computer using an ISP programmer and upload the code from `main.cpp`.

## Code Explanation
### Libraries
- `Arduino.h` - Core library for Arduino functionality with ATmega32.
- `LiquidCrystal_I2C.h` - Library for controlling the 16x2 I2C LCD.

### Constants
- `lm35Pin` - Defines analog pin `PA0` to which the LM35 is connected.
- `lcd` - Initializes an I2C LCD with address `0x27` and size 16x2.

### `setup()`
1. **ADC Setup**: Configures the ADC to use `AVCC` as the reference voltage and enables it with a prescaler of 128.
2. **LCD Initialization**: Sets up the LCD and turns on the backlight.

### `readADC()`
This function reads the ADC value from the selected channel. The channel is chosen by masking and adjusting the ADMUX register. The function waits until the conversion is complete and returns the 10-bit ADC result.

### `loop()`
1. **Temperature Reading and Conversion**: 
   - The analog voltage from the LM35 is read, then converted to millivolts (mV).
   - The temperature in Celsius is calculated as `temperatureC = mV / 10`.
2. **LCD Update**:
   - If the temperature change is greater than 0.1°C, the temperature is displayed.
   - The degree symbol (°) is displayed using `lcd.write((char)223);`.

### Custom Character for Degree Symbol
The code uses a predefined character code (ASCII 223) to display the degree symbol, which is compatible with most I2C LCD libraries.

## Usage
- Power the setup, and the LCD will display the temperature in real-time.
- Temperature updates occur only if there is a significant change (> 0.1°C), conserving LCD resources and enhancing readability.

## License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for more details.
