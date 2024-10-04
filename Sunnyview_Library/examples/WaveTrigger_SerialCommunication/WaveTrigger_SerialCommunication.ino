#include <Servo.h>
#include "Sunnyview.h"

Servo servoLeft;  // create servo object to control a servo
Servo servoRight;

WaveTrigger wav(9600);

// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  servoLeft.attach(4, 1000, 1900);  // attaches the servo on pin 9 to the servo object
  servoRight.attach(3, 1000, 1900);

  Serial.begin(9600);
 
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  wav.begin();
   if(!wav.isConnected()){
    //If not successful report the error code
    Serial.print("Failed to connect! Error code: ");
    Serial.println(wav.getLastError());
    //Error code 2 = Unknown device - message likely failed to send or board cannot reply
    //Error code 3 = unknown version - The board needs the latest firmware version OR the communication is unreliable
  }
  else{
    //If succesful
    Serial.print("Connected Successfully! Version Number: ");
    Serial.println(wav.getSystemInfo().version);
  }
}

void loop() { 
  int sensorVal = digitalRead(2);
  //print out the value of the pushbutton
  //Serial.println(sensorVal);
    
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == LOW) {
    servoLeft.write(0);
    servoRight.write(0);
    delay(250);

    digitalWrite(8, HIGH);
    //wav.runTrack(1, true);
    delay(1000);
    digitalWrite(8, LOW);

    servoLeft.write(90);
    servoRight.write(90);
    delay(1000);
    
  } 
}
