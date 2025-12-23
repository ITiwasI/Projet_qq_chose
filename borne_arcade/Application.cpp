#include "Application.h"

//────────────────────────────── Pin planning

#define UP_BUTTON_PIN     3
#define DOWN_BUTTON_PIN   4
#define LEFT_BUTTON_PIN   5
#define RIGHT_BUTTON_PIN  6
#define CENTER_BUTTON_PIN 7

//────────────────────────────── Menu variables

#define MENU_LENGTH 3

//────────────────────────────── Constructor/Destructor

Application::Application() {}
Application::~Application() {}

//────────────────────────────── Actually used functions

void Application::init(void) {
  // Variable init
  _selector = 0;
  _lastButtonState = 0;
  _pressTime = 0;

  // Communication to screen/debug
  Serial.begin(38400);
  while(!Serial) {};
  Serial.println("Starting communication");

  // Hadware objects init
  upButton.init(UP_BUTTON_PIN);
  downButton.init(DOWN_BUTTON_PIN);
  leftButton.init(LEFT_BUTTON_PIN);
  rightButton.init(RIGHT_BUTTON_PIN);
  centerButton.init(CENTER_BUTTON_PIN);
  Serial.println("Hardware ready");
}

void Application::updateSelector() {
  /* 
   * Behavior : ups the value on rising right click,
   * Holding it for more than 1 sec uninterrupted make it scroll
   */
  
  bool left = leftButton.isPressed();
  bool right = rightButton.isPressed();

  if (left && right) {
    // Indicates conflict
    _pressTime = -1;

  } else if (left) {
    if (_lastButtonState == 0) {
      // Rising edge of button press
      _selector = (_selector-1) % MENU_LENGTH;
      _lastButtonState = -1;
    } else if (_lastButtonState == -1 && _pressTime >= 0) {
      // Already holding for more than 50 ms and not interrupted
      _pressTime += 50;
    } else if (_lastButtonState == -1 && _pressTime >= 1000) {
      // Already holding for a second, no conflicts, scroll at 5Hz
      _selector = (_selector-1) % MENU_LENGTH;
      // Only 195 because the final delay calculation limits itself to 5ms (for consistency)
      delay(195);
      // Still increments time if we want to add another scroll speed past X seconds
      _pressTime += 200;
    }
  } else if (right) {
    // Same for right, increments
    if (_lastButtonState == 0) {
      _selector = (_selector+1) % MENU_LENGTH;
      _lastButtonState = 1;
    } else if (_lastButtonState == 1 && _pressTime >= 0) {
      _pressTime += 50;
    } else if (_lastButtonState == 1 && _pressTime >= 1000) {
      _selector = (_selector+1) % MENU_LENGTH;
      delay(195);
      _pressTime += 200;
    }
  } else {
    _lastButtonState = 0;
    _pressTime = 0;
  }
}

void Application::run(void) {
  // Keep track of time to get exactly 50ms ticks
  unsigned long t0 = millis();

  // Updates and send selector value to screen
  updateSelector();
  Serial.println(_selector);

  // Game selection detection
  if (centerButton.isPressed()) {
    switch (_selector) {
      case 1:
        // Launch game 1...
        break;
      default :
        // Game 0
        break;
    }
  }

  // Delay 50ms total, minimum 5ms in case of scroll
  if (50 - (millis()-t0) > 5){
    delay(50 - (millis()-t0));
  }
  delay(5);
}
