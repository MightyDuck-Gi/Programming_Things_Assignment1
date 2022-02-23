# Programming_Things_Assignment1


Intro

This is an repo of my assignment for programming things, where we coded pololu zumo 32u4 robot to perform tasks given to us in assignment breif. The purpose of this assignment was to simulate a "search and rescue", where the zumo robot is required to navigate through corridoor and keep within lines.

In order to achive this task, different libaries and aspects were used to complete these. For example the line sensors to keep within the corridoors and rooms, the wireless serial communications between xBee and GUI, as well as using the motors to move the zumo.


GUI

![image](https://user-images.githubusercontent.com/72032298/155357265-f3fab9b5-14b6-46f1-898d-0562b9bfd6ac.png)

The GUI was written in python as python comes with Tkinter, a python tool kit that allows to make GUI. There was 2 reason as to why i chose this option, 1- it allows simple coding but effective for this assignment, 2- python has PySerial libary which allows the connection between serial port and GUI. Upon press each button on the gui it will show the user below what command its performing and what the user is required to do.


Achievements 

[x] Task 1 - First task of this assignment is was to be able to move the Zumo bot with GUI (w,a,s,d,), and it should be controlled wirelessly using xBee communications. I used a reference i found online to complete this first task (https://thebrickinthesky.wordpress.com/2015/02/08/python-arduino-xbee-zumo-robot/), reading this page i was able to see how the code was written to allow the zumo to be controlled and change it to fit my project.

[x] Task 2 - Second task was to allow the zumo robot to be able to traverse the maze automaticly and keep within the corridoor using the linesensors. This was done using the borderdetection example code that comes with the zumo libary, and doing further research, i was able to discover that the line sensors can be reverse to detect black borders instead of white.

[x] Task 3 - This task was pretty much extension of task 2, and essentially when it hit the end of corridoor or T-junction, the control should be given back to the user so that the user can choose which dierectoin the robot needs to go in. It will once again return the controls back to the user if it hits another dead end. 

[x] Task 4 - Forth task should allow the robot to automaticly turn after user inputs where the robot should go after hitting the wall. The user can select to go 90 degrees left or right or do 180 degree if it hits a dead end. 


Key Issues & Resolves

Line sensor - Main issue i had when trying to code this part, was that the the bot would think the edge of coridoor was dead end and would hand the controls back to the user inorder to correct itself. However, upon further inspection, i realised that once any of the sensor goes of, it should go slower and go forward slightly to see if it will activate other 2 sensors. This ensure that if the other to sensors activate then its a dead-end, otherwise it should know that it is and edge of corridoor and should adjust to keep within the borders.

Tkinker GUI serial Comm - Another major issue i faced when doing this project was getting the gui to work with the arduino serial port, for Tkinter to be able to use serial it required to install additional libary, however install this libary was difficult as you would have to change your systems environment variable in order to grant access to makes changes to the files. I was able to over come this buy going into (This Pc-> Properties -> Advanced system settings -> Environment Variables -> System path) and adding few lines and changes few directory to allow this installation. 

This was created by Emran Islam Hamdu - B9016310 - BEng Software Engineering 
