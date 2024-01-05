<p align="center">
  <img src="https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/assets/131162335/ae3fdf00-2a4e-4214-85f3-08daa32d2aa6">
</p>
<p align="center">
  <img alt="Static Badge" src="https://img.shields.io/badge/ANUlab-Atrovel-blue">
  <img alt="GitHub License" src="https://img.shields.io/github/license/A-N-Ulab/ATROVEL-arduino_calculator">
  <img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/A-N-Ulab/ATROVEL-arduino_calculator">
</p>

# Make your own
### Components
* Arduino Nano/Arduino Pro Micro/Raspberry Pi pico - (I'm using RPI pico), anything small enough to fit inside will work
* 0.96 display
* 4x4 button matrix
* two 6x6mm buttons
* two 3mm led's
* 18650 holder
* 18650 Li-ion battery
* case
* tp4056 BMS

### Case
Download latest release. There are two files

### Electric Diagram
Wiring diagram for RPI pico
[Schematic Atrovel.pdf](https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/files/13798303/Schematic.Atrovel.pdf)
It requires to modify TP4056 BMS like that:
![20231230_151600](https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/assets/131162335/efb826f4-d096-450f-b4ba-79e10b34b2af)

### Software
Download latest release

#### Known problems
If you ar going to do some calculations e.g. 2+2 and then press square root of it, it won't work. But if you press 4 and then square root of it, it will work.

#### **READ THIS IF YOU ARE USING RASPBERRY PI PICO**'
For the display to work you're gonna have to declare that you are using different pins as I2C that default. Below is how i did it but there probably is a better way.
Find file ```pinmode_arduino.h```, find it here in Windows installations of Arduino IDE:
```C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\hardware\mbed_rp2040\2.5.2\variants\RASPBERRY_PI_PICO```
Modify as below:
![sda](https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/assets/131162335/0a93c4d0-0f1c-4c15-99ae-a7676c97000a)

# License
This project is licensed under a [Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/).  
![CC BY 4.0](https://i.creativecommons.org/l/by/4.0/88x31.png)


