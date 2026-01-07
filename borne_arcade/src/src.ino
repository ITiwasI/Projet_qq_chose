// Test programm to test the compilation of the project, component-wise
// Also to see all src files in the Arduino IDE

//#include "testGame.h"
#include "button.h"

button left;
button center;
button right;

void setup() {
  Serial.begin(115200);
  left.init(2);
  center.init(3);
  right.init(4);
}

void loop() {
  if(left.isPressed()) Serial.print("L");
  else Serial.print(" ");
  if(center.isPressed()) Serial.print("C");
  else Serial.print(" ");
  if(right.isPressed()) Serial.print("R");
  else Serial.print(" ");
  Serial.println();
  delay(50);
}