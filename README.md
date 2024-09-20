# Fitness Watch Project

This project is a basic fitness tracking device built with an Arduino, an LIS3DHTR accelerometer, and a DS3231 Real-Time Clock (RTC) module. It tracks steps, calculates calories burned, displays distance traveled, and provides the current date and time.

## Features

- **Step Tracking:** Utilizes the LIS3DHTR accelerometer to detect steps and update the step count in real time.
- **Calorie Calculation:** Automatically calculates calories burned based on the number of steps taken.
- **Distance Measurement:** Provides the distance covered in both kilometers and miles based on the step count.
- **Date & Time:** Displays the current date and time using the DS3231 RTC module.
- **Mode Switching:** Use a button to switch between different display modes, including step count, calories burned, distance traveled, and more.
- **Customizable Variables:** Modify average calorie and step distance values for accurate results.

## Components Used

1. **LIS3DHTR Accelerometer (I2C):** Measures acceleration to count steps.
2. **DS3231 RTC (I2C):** Keeps track of the current date and time.
3. **Button:** Used to switch between modes.
4. **Arduino Board (Uno or GroveBoard):** Runs the program and manages the sensors.

## How to Connect the Components

| Component                 | Arduino Pin                 | Description                                       |
|---------------------------|-----------------------------|---------------------------------------------------|
| **LIS3DHTR Accelerometer** | SDA (A4), SCL (A5)          | Connect to the I2C pins for communication.        |
| **DS3231 RTC Module**      | SDA (A4), SCL (A5)          | Shares I2C pins (A4, A5) with the accelerometer.  |
| **Button**                 | Digital Pin D4              | Connect the button to digital pin D4 to change modes. |
| **Power (VCC)**            | 5V                         | All components are powered from the Arduino's 5V pin. |
| **Ground (GND)**           | GND                        | Connect the GND of all components to the Arduino's GND pin. |

### Schematic and Pictorial Circuit

For a detailed connection diagram, check out the following resources:

- **Schematic Diagram:** [Schematic Link](#)
- **Pictorial Circuit:** [Pictorial Circuit Link](#)

## How to Use

1. **Step Tracking Mode:** Shows the current number of steps you’ve taken.
2. **Calories Mode:** Displays the estimated calories burned based on your steps.
3. **Distance Mode:** Shows the distance traveled in both kilometers and miles.
4. **Time & Date Mode:** Displays the current date and time.
5. **Welcome & Information Mode:** Displays a welcome message and project details.

Switch between modes by pressing the button.

## Future Enhancements

1. **Temperature Sensor Integration:** Add a temperature sensor (like DHT11 or DS18B20) to measure and display real-time temperature data alongside other fitness metrics.
   - Alternatively, connect the fitness watch to a weather API to retrieve and display local temperature data.

2. **Bluetooth Connectivity (HC-05 Module):** 
   - Integrate the HC-05 Bluetooth module to sync the fitness tracker with a smartphone.
   - Receive notifications and calls directly on the watch, providing real-time alerts for incoming messages, calls, and other notifications.

3. **OLED Display:** Display all metrics (steps, calories, time, temperature, notifications) on an OLED or other suitable display for a more user-friendly interface.

4. **Heart Rate Sensor:** Add a heart rate sensor to track and display heart rate data, expanding the fitness capabilities of the watch.

## Resources/Help

Here are some helpful resources for building and enhancing the fitness watch:

- **Arduino Official Website:** [https://www.arduino.cc/](https://www.arduino.cc/)
- **LIS3DHTR Accelerometer Documentation:** [LIS3DHTR Datasheet](https://www.st.com/resource/en/datasheet/lis3dh.pdf)
- **DS3231 RTC Module Guide:** [DS3231 RTC Documentation](https://lastminuteengineers.com/ds3231-rtc-arduino-tutorial/)
- **Button Control in Arduino:** [Button Tutorial](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button)
- **GroveBoard Manual:** [Manual](https://files.seeedstudio.com/wiki/Grove-Beginner-Kit-For-Arduino/res/Grove-Beginner-Kit-For-ArduinoPDF.pdf)
- **GroveBoard Link:** [Buy Here](https://www.seeedstudio.com/Grove-Beginner-Kit-for-Arduino-p-4549.html)

If you need further help or tutorials, here are some useful links:

- **How to Install Visual Studio Code on Windows 11:** [YouTube](https://www.youtube.com/watch?v=cu_ykIfBprI)
- **How to Program Arduino in VSCode:** [YouTube](https://www.youtube.com/watch?v=dany7ae_0ks)
- **LIS3DH Accelerometer Tutorial:** [YouTube](https://www.youtube.com/watch?v=C09hG8OCBEk)
- **Getting Started With DS3231 RTC Module:** [YouTube](https://www.youtube.com/watch?v=RoSVrVVMy0c)
- **How to Use a Button with an Arduino:** [YouTube](https://www.youtube.com/watch?v=yBgMJssXqHY)
- **Grove Beginner Kit for Arduino Review:** [YouTube](https://
