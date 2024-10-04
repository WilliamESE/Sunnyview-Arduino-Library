#include "Sunnyview.h"

//Creates a button on port 2
SunnyButton drawBtn(2);

void setup() {
  //Adds the LED to the button on port 5
  drawBtn.withLED(5);
}

void loop() {
  if (drawBtn.isPressed())
    drawBtn.setLEDOn();
  else
    drawBtn.setLEDOff();
}
