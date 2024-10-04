#include "Sunnyview.h"

Hbridge motor(3,6);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  motor.begin();
}

// the loop function runs over and over again forever
void loop() {
  //Rampup
  for(int x=0;x<255;x++){
    motor.forwards(x);
    delay(20);
  }
  
  //Remain forwards for 1 second
  delay(1000);
  
  //ramp down
  for(int x=255;x>0;x--){
    motor.forwards(x);
    delay(20);
  }

  //Stoped for 1 second
  delay(1000);

  //Ramp backwards
  for(int x=0;x<255;x++){
    motor.backwards(x);
    delay(20);
  }

  delay(1000);
  motor.stop();
}
