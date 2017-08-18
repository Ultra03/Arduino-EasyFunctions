#include <CoDrone.h>
#include "Ultra.h"

Ultra::Ultra() {
    temp[0] = 0;
    temp[1] = 0;
    temp[2] = 0;
    temp[3] = 3;
    password[0] = 1;
    password[1] = 2;
    password[2] = 3;
    password[3] = 4;
    index = 0;
    tries = 0;
}

void Ultra::startup() {
	CoDrone.begin(115200);
	CoDrone.AutoConnect(NearbyDrone);
}

void Ultra::freeflyLoop() {
  byte bt1 = digitalRead(11);       // reads the far left button and saves it to btn1
  byte bt4 = digitalRead(14);       // reads the middle button and saves it to btn4
  byte bt8 = digitalRead(18);       // reads the far right button and saves it to btn8

  // Stop when the left butotn is pressed, but none of the others are
  if (bt1 && !bt4 && !bt8)
  {
    CoDrone.FlightEvent(Stop);      // This command stops the drone (it turns off the motors)
  }

  // try to land when the right button is pressed and no others are
  if (!bt1 && !bt4 && bt8)
  {
     CoDrone.FlightEvent(Landing);  // Tells the drone to land (slowly lowers until it hits the ground and then turns off)
  }

  if(digitalRead(14) == 1) {
    CoDrone.LedColor(EyeHold, Yellow, 100);
    delay(100);
    CoDrone.LedColor(ArmHold, Yellow, 100);
    delay(100);
  }

  if(digitalRead(16) == 1) {
    CoDrone.LedColor(EyeFlicker, Aqua, 100);
    delay(100);
    CoDrone.LedColor(ArmFlow, Cornsilk, 10);
    delay(100);
  }

  // PAIRING is set to true in AutoConnect if they connect together
  if (PAIRING == true)  // Check to see that we are paired before trying to fly               
  {
    // reads the joystick (analogRead(A#)) and then converts it into a value that the drone can use (AnalogScaleChange())
    // if any of the joysticks move backwards compared to the drone (up is down or left is right), add -1 * at the start
    // it will change the direction the drone moves when you move the joystick
    YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));   // YAW (turn left or right), port A3, reversed
    THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));  // THROTTLE (height), port A4, not reversed
    ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));  // ROLL (tilt left or right), port A5, reversed
    PITCH = CoDrone.AnalogScaleChange(analogRead(A6));      // PITCH (tilt front or back), port A6, not reversed
    
    CoDrone.Control(SEND_INTERVAL); // sends the values to the codrone, it will make sure that SEND_INTERVAL (~50ms) time has passed before it sends again 
  }

}

void Ultra::passwordInput() {
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);

  bool correct = false;

  while(!correct) {
  if(index == 4) {
    if(temp[0] == password[0] && temp[1] == password[1] && temp[2] == password[2] && temp[3] == password[3]) {
      CoDrone.Buzz(5000, 1);
      CoDrone.Buzz(1000, 1);
      CoDrone.Buzz(5000, 1);
      correct = true;
    } else {
      CoDrone.Buzz(100, 1);
      tries = tries + 1;
      index = 0;
      temp[0] = 0;
      temp[1] = 0;
      temp[2] = 0;
      temp[3] = 0;
    }
    while(tries == 3) {
      CoDrone.Buzz(250, 1);
    }
  }
  
  if(temp[index] != 0) {
    index = index + 1;
    CoDrone.Buzz(500, 1);
  }
  
  if(digitalRead(11)) {
    temp[index] = 1;
    while(digitalRead(11) == 1) {
    
    }
  
 } else if(digitalRead(12)) {
    temp[index] = 2;
    while(digitalRead(11) == 1) {
      
    }
 } else if(digitalRead(13)) {
    temp[index] = 3;
    while(digitalRead(13)) {
      
    }
 } else if(digitalRead(14)) {
    temp[index] = 4;
    while(digitalRead(14) == 1) {
      
    }
 } else if(digitalRead(16)) {
    temp[index] = 5;
    while(digitalRead(16) == 1) {
      
    }
  } else if(digitalRead(17)) {
    temp[index] = 6;
    while(digitalRead(17) == 1) {
      
    }
 } else if(digitalRead(18)) {
    temp[index] = 7;
    while(digitalRead(18)) {
      
    }
 }
}
}