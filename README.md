<p align="center">
  <img src="https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/assets/131162335/ae3fdf00-2a4e-4214-85f3-08daa32d2aa6">
</p>
<p align="center">
  <img alt="Static Badge" src="https://img.shields.io/badge/ANUlab-Atrovel-blue">
  <img alt="GitHub License" src="https://img.shields.io/github/license/A-N-Ulab/ATROVEL-arduino_calculator">
  <img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/A-N-Ulab/ATROVEL-arduino_calculator">
</p>

# Story
This calculator is an effect of a project started in school. We were learning how to use 8x8 button matrix with arduino and I was a little bit bored so I started making a calculator. I have always wanted to make one. I acknowledge, this is not the best solution you can find but it works. All you need to do is solder (or not) everything and put it in some sort of case, you can use the one provided in this repository or something completely different.   
**Disclaimer**: There is a high chance that 8x8 matrix is not connected properly. I will be able to check it in a few days.   

#### I hope you will enjoy this project as much as i did

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

### Case and software
Download latest [release](https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/releases/latest)

### Electric Diagram
Wiring diagram for RPI pico, also comes with the lates release.
[Schematic Atrovel.pdf](https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/files/13798303/Schematic.Atrovel.pdf)
Wiring of Atrovel requires to modifying TP4056 BMS like that:  
<img width="200" src="https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/assets/131162335/d48bbf6a-5378-418c-9f0d-4324b425b3f6">


#### Known problems
If you are going to do some calculations e.g. 2+2 and then press square root of it, it won't work. But if you press 4 and then square root of it, it will work. It might be fixed in another release of Atrovel.

#### **READ THIS IF YOU ARE/WILL BE USING RASPBERRY PI PICO**'
For the display to work you're gonna have to declare that you are using different pins as I2C than default. Below is my solution - changing default I2C pins.
Find file ```pinmode_arduino.h``` here in Windows installations of Arduino IDE:
```C:\Users\USERNAME\AppData\Local\Arduino15\packages\arduino\hardware\mbed_rp2040\2.5.2\variants\RASPBERRY_PI_PICO```
Modify as below:
![sda](https://github.com/A-N-Ulab/ATROVEL-arduino_calculator/assets/131162335/0a93c4d0-0f1c-4c15-99ae-a7676c97000a)

# License
This project is licensed under a [Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/).  
![CC BY 4.0](https://i.creativecommons.org/l/by/4.0/88x31.png)


