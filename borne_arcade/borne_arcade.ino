#include "application.h"

application myApplication;

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  myApplication.init();
}

void loop() 
{
  myApplication.run();
}
