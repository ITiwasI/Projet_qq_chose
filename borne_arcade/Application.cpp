#include "application.h"

//────────────────────────────── Pin planning

#define LEFT_BUTTON_PIN   2
#define RIGHT_BUTTON_PIN  4
#define CENTER_BUTTON_PIN 3

//────────────────────────────── Menu variables

#define MENU_LENGTH 3

//────────────────────────────── Constructor/Destructor

application::application() {}
application::~application() {}

//────────────────────────────── Actually used functions

void application::init(void) {
  // Variable init
  _selector = 0;
  _lastButtonState = 0;

  // Communication to screen/debug
  Serial.begin(38400);
  while(!Serial) {};
  Serial.println("Starting communication");

  // Hadware objects init
  leftButton.init(LEFT_BUTTON_PIN);
  rightButton.init(RIGHT_BUTTON_PIN);
  centerButton.init(CENTER_BUTTON_PIN);
  Serial.println("Hardware ready");
}

void application::updateSelector() {
  
  bool left = leftButton.isPressed();
  bool right = rightButton.isPressed();

  if (left && _lastButtonState == 0) {
      // Rising edge of button press
      _selector = (_selector+MENU_LENGTH-1) % MENU_LENGTH;
      _lastButtonState = -1;
  } else if (right && _lastButtonState == 0) {
      _selector = (_selector+1) % MENU_LENGTH;
      _lastButtonState = 1;
  } else if (!left && !right) {
    _lastButtonState = 0;
  }
}

void application::runGame(void) {
  if (_selector == 0) {
    currentGame = testGame();
    currentGame.init(&leftButton, &rightButton);
  }  
}

void application::run(void) {
  // Keep track of time to get exactly 50ms ticks
  unsigned long t0 = millis();

  // Updates and send selector value to screen
  updateSelector();
  Serial.println(_selector);

  // Game selection detection
  if (centerButton.isPressed()) {
    Serial.print("runGame");
    Serial.println(_selector);
    runGame();
  }

  // Delay 50ms total, minimum 5ms in case of scroll
  if (50 - (millis()-t0) > 0){
    delay(50 - (millis()-t0));
  }
}
