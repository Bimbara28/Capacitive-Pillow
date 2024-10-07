# Capacitive Touch Controller README

## Overview

This project implements a capacitive touch controller using Arduino to simulate arrow key presses on a keyboard. The controller consists of four touch-sensitive buttons corresponding to the left, right, up, and down arrow keys. The sensitivity of each button is dynamically adjusted based on user interaction, providing an improved user experience.

## Features

- **Capacitive Touch Sensors:** Four capacitive sensors are used to detect touch.
- **Dynamic Threshold Adjustment:** The touch sensitivity dynamically adjusts based on the user's interaction, ensuring reliable performance.
- **Auto Calibration:** The system recalibrates itself after periods of inactivity, enhancing accuracy.
- **Keyboard Emulation:** The controller sends keyboard commands to simulate arrow key presses.

## Hardware Requirements

- **Arduino Board:** Any compatible Arduino board (e.g., Arduino Uno, Leonardo).
- **Capacitive Touch Sensors:** Four sensors connected to the designated pins.


## Wiring Diagram

| Capacitive Pin | Arduino Pin |
|----------------|-------------|
| Left Arrow     | Pin 3      |
| Right Arrow    | Pin 10     |
| Up Arrow       | Pin 12     |
| Down Arrow     | Pin 2      |

Make sure to connect the capacitive sensors to the specified pins on your Arduino.

## Software Requirements

- **Arduino IDE:** Download and install the latest version of the Arduino IDE.
- **Libraries:**
  - **CapPin Library:** For capacitive sensing. You can find it [here](https://github.com/moderndevice/CapSense).
  - **Keyboard Library:** For sending keyboard commands (comes pre-installed with Arduino IDE).

## Installation

1. **Download the Code:**
   Copy the provided code into your Arduino IDE.

2. **Install Required Libraries:**
   Make sure to install the **CapPin** library if you haven’t done so already.

3. **Upload the Code:**
   Connect your Arduino board to your computer and upload the code.

4. **Open the Serial Monitor:**
   Open the Serial Monitor in the Arduino IDE to observe the sensor values and interaction feedback.

## Usage

- **Touch the Sensors:** 
  - Touch the left sensor to simulate the left arrow key press.
  - Touch the right sensor for the right arrow key.
  - Touch the up sensor for the up arrow key.
  - Touch the down sensor for the down arrow key.

- **Monitor Output:**
  The Serial Monitor will display the current sensor readings and whether the keys are pressed or released.

- **Auto Calibration:**
  After 10 seconds of inactivity, the system recalibrates the sensor baselines to adapt to any environmental changes.

## Code Explanation

### Key Functions

- `setup()`: Initializes serial communication, calibrates the sensor baselines, and sets dynamic thresholds.
- `loop()`: Continuously checks the sensor values, adjusts the thresholds, and handles key press events.
- `handleKeyPress()`: Manages key press and release actions, updating the state of the keys accordingly.
- `recalibrateSensors()`: Recalibrates the sensor baselines and resets dynamic thresholds.
- `calibrateSensor()`: Averages sensor readings over multiple samples to establish a baseline.
- `adjustThreshold()`: Adjusts the touch sensitivity threshold based on user interaction.


# Step-by-Step Explanation of the Capacitive Touch Controller Code

## Step-by-Step Breakdown

1. **Include Libraries:**
   - The code imports two libraries that provide special functions. The first library helps read touch inputs from the sensors, and the second library allows the Arduino to send keyboard commands to a computer.

2. **Setup Touch Pins:**
   - The code defines four touch sensors, each connected to a specific pin on the Arduino. Each sensor corresponds to an arrow key.

3. **Define Key Presses:**
   - Each arrow key is assigned to a variable. This means that when a sensor is touched, it knows which key to simulate.

4. **Track Key States:**
   - Variables are created to keep track of whether each key is currently being pressed. They start as "not pressed."

5. **Set Up Baseline and Thresholds:**
   - Variables are used to store baseline values (normal sensor readings when not touched) and thresholds (sensitivity levels). These will help determine how sensitive each button is.

6. **Calibration Settings:**
   - The code establishes how often the system recalibrates itself. If it hasn’t been used for a certain amount of time, it adjusts its sensitivity.

7. **Setup Function:**
   - This function runs once when the Arduino is powered on. It sets up communication between the Arduino and the computer.

8. **Calibration of Sensors:**
   - The code calibrates each sensor by taking multiple readings to find a normal (baseline) value for each sensor.

9. **Set Initial Sensitivity:**
   - The code establishes initial sensitivity levels for the buttons, slightly above the baseline values.

10. **Loop Function:**
    - This function runs continuously after the setup. It constantly checks the status of the sensors.

11. **Check for Inactivity:**
    - If no buttons are touched for a certain time, the system recalibrates itself.

12. **Read Sensor Values:**
    - The code checks the current readings from each sensor to see how much touch they are detecting.

13. **Adjust Sensitivity:**
    - This section updates the sensitivity of each button based on how they are being used. If a button is pressed, it becomes more sensitive to subsequent touches.

14. **Print Sensor Data:**
    - The code prints the current sensor readings and their thresholds to the Serial Monitor for debugging.

15. **Handle Key Presses:**
    - A function checks if the sensor readings exceed the threshold. If so, it simulates pressing the corresponding arrow key.

16. **Key Press Handling Function:**
    - This function checks if the current reading indicates a button press. If it does, it sends the keyboard command for that arrow key and updates the state.

17. **Recalibration Function:**
    - If the sensors need recalibration, this function reads new baseline values to reset their sensitivity.

18. **Sensor Calibration:**
    - This function averages several readings from a sensor to establish a reliable baseline.

19. **Adjusting Sensitivity:**
    - This function adjusts the sensitivity threshold based on current touch readings. It makes the button more responsive if pressed and less sensitive over time if not used.


### Customization

- You can adjust the `recalibrationTime` and `idleTimeout` variables to change how often the sensors recalibrate and how long the system waits before recalibrating.

## Troubleshooting

- **No Key Press Detected:** Ensure that the sensors are properly connected and that the code has been uploaded correctly.
- **Fluctuating Sensor Values:** Check for environmental factors (e.g., humidity or electrical noise) that might affect the sensor readings.

## License

This project is open-source. Feel free to modify and distribute it according to your needs.


## Conclusion

In summary, this code allows a user to interact with their computer using touch-sensitive buttons that simulate arrow key presses. It ensures that the buttons are responsive, adapts to the user's touch, and recalibrates automatically to maintain accuracy. If you have any questions about specific parts or need further clarification, feel free to ask!
