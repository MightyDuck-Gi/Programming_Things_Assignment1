#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Buzzer buzzer;

#define QTR_THRESHOLD  700 /*Line detection threshold*/
#define NUM_SENSORS 3      /*0 is left sensor, 1 is middle sensor, and 2 is right sensor*/
#define MOTOR_SPEED 100 /*Default speed for motors*/
#define MOTOR_TURN_SPEED 200/*Default turn speed for motors*/
#define LEFT 0
#define RIGHT 1

unsigned int lineSensorValues[NUM_SENSORS];
const uint8_t sensorThreshold = 5;

void setup() {
  Serial1.begin(9600); /* Begin a Serial1 connection*/
  lineSensors.initThreeSensors(); /*Initiate the three line sensors*/
  proxSensors.initFrontSensor(); /*Initiate the front sensors */

}

void loop() {

  while (Serial1.available()>0) {

      int direction = Serial1.read(); /*Reads users input and assigns it*/
      String name = "";

      switch (direction){
        case'w': case 'W':{ /*If W is entered go forward */
          name = "Forward";
          Serial1.println("Forward \n"); /*prints out the command to the user*/
          motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
          delay(150);
          motors.setSpeeds(0, 0);
          return;
        }

        case 'a': case'A':{ /*If A is entered turn left*/
          name = "Left";
          Serial1.println("Left turn \n"); /*prints out the command to the user*/
          motors.setSpeeds(-MOTOR_SPEED, MOTOR_SPEED);
          delay(150);
          motors.setSpeeds(0, 0);
          return;
        }

        case 'd': case'D': {/*If D is entered turn right*/
          name = "Right";
          Serial1.println("Right turn \n"); /*prints out the command to the user*/
          motors.setSpeeds(MOTOR_SPEED, -MOTOR_SPEED);
          delay(150);
          motors.setSpeeds(0, 0);
          return;
        }

        case 's': case'S': {/*If S go backwards*/
          name = "Backward";
          Serial1.println("Backwards \n"); /*prints out the command to the user*/
          motors.setSpeeds(-MOTOR_SPEED, -MOTOR_SPEED);
          delay(150);
          motors.setSpeeds(0, 0);
          return;
        }

        case 'r': case'R': {/*If R is entered turn right 90 degrees*/
          name = "Right";
          Serial1.println("Right turn 90 degrees \n"); /*prints out the command to the user*/
          motors.setSpeeds(MOTOR_TURN_SPEED, -MOTOR_TURN_SPEED);
          delay(330);
          motors.setSpeeds(0, 0);
          return;
        }

        case 'l': case'L': {/*If L is entered turn right 90 degrees*/
          name = "Left";
          Serial1.println("Left turn 90 degrees \n"); /*prints out the command to the user*/
          motors.setSpeeds(-MOTOR_TURN_SPEED, MOTOR_TURN_SPEED);
          delay(330);
          motors.setSpeeds(0, 0);
          return;
        }

        case'b': case'B': {
          name = "180";
          Serial1.println("180 \n"); /*prints out the command to the user*/
          motors.setSpeeds(MOTOR_TURN_SPEED, -MOTOR_TURN_SPEED);
          delay(660);
          motors.setSpeeds(0, 0);
          return;
        }
        
        case 'c': case 'C': { /* If O is entered run task 3*/
          name= "Manual Navigation";
          Serial1.println("Manual Navigation: Press c at end of corridoor. \n"); /*prints out to the user*/
          manualNavigator(); /*calling the function from below*/
          return;
        }
                
        case 'x': case'X': {
          name= "Automatous Navigation";
          Serial1.println("Manual Navigation: Press c at end of corridoor. \n");
          autoNavigator();
          return;
        }
        }
      }
}

void manSteer() {
  String name = "";

  Serial1.print("Make a turn using 'A' or 'D', then press 'C' to resume. \n");/*prints out to the user*/
  bool status = true;/*Reads users input and assigns it*/

  while(status) {
    int direaction = Serial1.read();

    switch(direaction) {
      case 'a': case'A':{ /*If A is entered turn left*/
        name = "Left";
        Serial1.println("Left turn \n"); /*prints out the command to the user*/
        motors.setSpeeds(-MOTOR_TURN_SPEED, MOTOR_TURN_SPEED);
        delay(200);
        motors.setSpeeds(0, 0);
        break;
      }

        case 'd': case'D': {/*If D is entered turn right*/
          name = "Right";
          Serial1.println("Right turn \n"); /*prints out the command to the user*/
          motors.setSpeeds(MOTOR_TURN_SPEED, -MOTOR_TURN_SPEED);
          delay(200);
          motors.setSpeeds(0, 0);
          break;
        }

        case 'c': case 'C': {
          name= "resume";
          Serial1.println("Resuming.\n"); /*prints out to the user*/
          status = false;
          manualNavigator(); /*calling the function from below*/
          break;
        }   
        return;
      }
    }
}

void autoSteer() {
 String name = "";

  Serial1.print("Make a turn using 'L' or 'R', then press 'C' to resume. \n");/*prints out to the user*/
  bool status = true;/*Reads users input and assigns it*/

  while(status) {
    int direaction = Serial1.read();

    switch(direaction) {
      case 'l': case'L':{ /*If A is entered turn left*/
        name = "Left";
        Serial1.println("Left turn 90 degrees \n"); /*prints out the command to the user*/
        motors.setSpeeds(-MOTOR_TURN_SPEED, MOTOR_TURN_SPEED);
        delay(330);
        motors.setSpeeds(0, 0);
        status = false;
        autoNavigator();
        break;
      }

    case 'r': case'R':{ /*If A is entered turn left*/
        name = "Right";
        Serial1.println("Left turn 90 degrees \n"); /*prints out the command to the user*/
        motors.setSpeeds(MOTOR_TURN_SPEED, -MOTOR_TURN_SPEED);
        delay(330);
        motors.setSpeeds(0, 0);
        status = false;
        autoNavigator();
        break;
      }
    case 'b': case'B':{ /*If A is entered turn left*/
        name = "180";
        Serial1.println("Turn 180 degrees \n"); /*prints out the command to the user*/
        motors.setSpeeds(-MOTOR_TURN_SPEED, MOTOR_TURN_SPEED);
        delay(660);
        motors.setSpeeds(0, 0);
        status = false;
        autoNavigator();
        break;
      }
      return;
    }
      
   }
  }

void autoNavigator(){
    bool i = true;

    while(i){ 

       lineSensors.read(lineSensorValues); /*assigns the line sensors to the array*/

       if(lineSensorValues[0] > QTR_THRESHOLD){/*checking to see if left sensor is higher than threshold*/
  
          motors.setSpeeds(50, 50);/*goes forward slightly*/
          delay(150);
          lineSensors.read(lineSensorValues); /*checks the sensors agani*/

        if(lineSensorValues[NUM_SENSORS - 1] > QTR_THRESHOLD && lineSensorValues[0] > QTR_THRESHOLD) {/*checking if both sensor are above threshold*/
          motors.setSpeeds(-50, -50);
          delay(300);
          motors.setSpeeds(0, 0);
          autoSteer(); /*calls function from above and gives control back to user*/
        }

        else {/*this will reverse and turn right slightly*/
          
          motors.setSpeeds(-MOTOR_SPEED, -MOTOR_SPEED);
          delay(200);
          motors.setSpeeds(MOTOR_SPEED, -MOTOR_SPEED);
          delay(80);
          motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
        }
       }

       
       else if (lineSensorValues[NUM_SENSORS - 1] > QTR_THRESHOLD){ /*checking the right sensor*/
          motors.setSpeeds(50, 50);
          delay(150);
          lineSensors.read(lineSensorValues);

          if(lineSensorValues[0] > QTR_THRESHOLD && lineSensorValues[NUM_SENSORS - 1] > QTR_THRESHOLD){ /*checking if both sensors are above threshold*/
            motors.setSpeeds(-50,-50);
            delay(300);
            motors.setSpeeds(0,0);
            autoSteer();/*calls function from above and gives control back to user*/
          }

          else{/*this will reverse and turn right slightly*/
            motors.setSpeeds(-MOTOR_SPEED, -MOTOR_SPEED);
            delay(200);
            motors.setSpeeds(-MOTOR_SPEED, MOTOR_SPEED);
            delay(80);
            motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
          }
       }

       else/* sensors dont detech anything and arent over threshold */
       {
        motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED); /*keep going forward*/
       }
       
      }
}

void manualNavigator(){
    bool i = true;

    while(i){ 

       lineSensors.read(lineSensorValues); /*assigns the line sensors to the array*/

       if(lineSensorValues[0] > QTR_THRESHOLD){/*checking to see if left sensor is higher than threshold*/
  
          motors.setSpeeds(50, 50);/*goes forward slightly*/
          delay(150);
          lineSensors.read(lineSensorValues); /*checks the sensors agani*/

        if(lineSensorValues[NUM_SENSORS - 1] > QTR_THRESHOLD && lineSensorValues[0] > QTR_THRESHOLD) {/*checking if both sensor are above threshold*/
          motors.setSpeeds(-50, -50);
          delay(300);
          motors.setSpeeds(0, 0);
          manSteer(); /*calls function from above and gives control back to user*/
        }

        else {/*this will reverse and turn right slightly*/
          
          motors.setSpeeds(-MOTOR_SPEED, -MOTOR_SPEED);
          delay(200);
          motors.setSpeeds(MOTOR_SPEED, -MOTOR_SPEED);
          delay(80);
          motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
        }
       }

       
       else if (lineSensorValues[NUM_SENSORS - 1] > QTR_THRESHOLD){ /*checking the right sensor*/
          motors.setSpeeds(50, 50);
          delay(150);
          lineSensors.read(lineSensorValues);

          if(lineSensorValues[0] > QTR_THRESHOLD && lineSensorValues[NUM_SENSORS - 1] > QTR_THRESHOLD){ /*checking if both sensors are above threshold*/
            motors.setSpeeds(-50,-50);
            delay(300);
            motors.setSpeeds(0,0);
            manSteer();/*calls function from above and gives control back to user*/
          }

          else{/*this will reverse and turn right slightly*/
            motors.setSpeeds(-MOTOR_SPEED, -MOTOR_SPEED);
            delay(200);
            motors.setSpeeds(-MOTOR_SPEED, MOTOR_SPEED);
            delay(80);
            motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
          }
       }

       else/* sensors dont detech anything and arent over threshold */
       {
        motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED); /*keep going forward*/
       }
       
      }
}
