#include "Sunnyview.h"

SunnyLED drawLight(5); //SunnyLED drawLight(5, true); to reverse the output, default is false

void setup() {
}

void loop() {
  //Blink the LED
  drawLight.setOn();
  delay(500);
  drawLight.setOff();
  delay(500);
}
