# PIC16F877A_HC05_Bluetooth
## Created 06/18/2023

In this project, I have used the Bluetooth protocol to send command from my phone to control the speed, as weel as the direction of a brushed DC motor.

Components:
- PIC16F877A
- L298N motor driver
- A brushed DC motor
- HC-05 Bluetooth IC

As the PIC16F877A opearates at 5V logic, while the HC-05 Blueatooth IC has the working voltage level 3.3V, we must use the voltage divider circuit so that both device can communicate with each other. You can referce to the circuit below

![Source: deepblueembedded.com](https://github.com/HarryNguyen2023/PIC16F877A_HC05_Bluetooth/assets/136590151/ea6cd9f5-9573-42a1-81f8-fae6e7288b5a)

Moreover, to connect and send command via mobile phone, we absolutely need an Bluetooth serial communication. For Android user, I suggest you guid using Serial Bluetooth Terminal, which is very user-friendly and can be downloaded directly from the App Store. Finaaly, there is the circuit that I created in practice.
(Note as I didn't have available 1k and 2k resistors, I used series of 330ohm resistors instead, but I recommend you to use the accurate resistor to ensure to stability of the communication)

![image](https://github.com/HarryNguyen2023/PIC16F877A_HC05_Bluetooth/assets/136590151/90f294c7-348d-4cb2-880c-e83942b8f5a4)

### References:
1. Bluetooth Module HC-05 With PIC Microcontroller Tutorial, https://deepbluembedded.com/bluetooth-module-hc05-interfacing-pic-microcontroller-tutorial/.

