#include "component.h"
#include "button.h"

button Bouton1;

void setup() {
  Bouton1.init(9);
  Serial.begin(9600);
}

void loop() {
  Serial.println(Bouton1.read());
}
