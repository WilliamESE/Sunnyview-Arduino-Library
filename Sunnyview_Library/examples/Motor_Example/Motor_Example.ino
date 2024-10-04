#include <Adafruit_NeoPixel.h>
#include <H_Bridge.h>
#include <SunnyButton.h>
#include <SunnyLED.h>
#include <SunnyMotor.h>
#include <Sunnyview.h>
#include <WaveTrigger.h>
#include <rp2040_pio.h>

#include "Sunnyview.h"

//Creates a motor on port 5
SunnyMotor mtr(5);

void setup() {
}

void loop() {
  //Run motor for 1 second
  mtr.run();
  delay(1000);
  mtr.stop();
}
