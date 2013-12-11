#include "Wire.h"
#include <ControLeo.h>

ControLeo_LiquidCrystal lcd;

static int adjustButton = 0;
static int selectButton = 0;
static int adjustRelay = 0;
static int adjustTime = 0;
static byte relay;
static int time;
String dispTime;

#define DEBOUNCE_INTERVAL  200

void setup() {
  // Set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);

  // The button is an input
  pinMode(CONTROLEO_BUTTON_PIN, INPUT);

}

void loop() {
  switch (getButton()) {
    case CONTROLEO_BUTTON_NONE:
      break;
    case CONTROLEO_BUTTON_TOP:
//      topCount++;
      lcd.setCursor(13, 0);
//      lcd.print(topCount);
      if (selectButton = 0) {
        adjustRelay++;
        lcd.print(adjustRelay);
      } else {
        adjustTime++;
        lcd.print(adjustTime);
      }
      break;
    case CONTROLEO_BUTTON_BOTTOM:
//      bottomCount++;
      lcd.setCursor(13, 1);
//      lcd.print(bottomCount);
      if (selectButton = 0) {
        switch (adjustRelay) {
          case 1:
            relay = 1;
            break;
          case 2:
            relay = 2;
            break;
          case 3:
            relay = 3;
            break;
          case 4:
            relay = 4;
            break;
        }
      } else {
          switch (adjustTime) {
            case 1:
              time = 14400;
              dispTime = "4 hours";
              break;
            case 2:
              time = 10800;
              dispTime = "3 hours";
              break;
            case 3:
              time = 7200;
              dispTime = "2 hours";
              break;
            case 4:
              time = 3600;
              dispTime = "1 hours";
              break;
            case 5:
              time = 2700;
              dispTime = "45 min";
              break;
            case 6:
              time = 1800;
              dispTime = "30 min";
              break;
            case 7:
              time = 900;
              dispTime = "15 min";
              break;
            case 8:
              time = 60;
              dispTime = "1 min";
              break;
          }
      }
      break;
  }
  
}

int getButton()
{
  static long lastChangeMillis = 0;
  long nowMillis = millis();
  int buttonValue;
  
  // If insufficient time has passed, just return none pressed
  if (lastChangeMillis + DEBOUNCE_INTERVAL > nowMillis)
    return CONTROLEO_BUTTON_NONE;
  
  // Read the current button status
  int pinValue = analogRead(CONTROLEO_BUTTON_PIN);
  
  // Interpret the value.  Allow for resistor variance
  if (pinValue < 100)
    buttonValue = CONTROLEO_BUTTON_BOTTOM;
  else if (pinValue > 900)
    buttonValue = CONTROLEO_BUTTON_NONE;
  else
    buttonValue = CONTROLEO_BUTTON_TOP;
  
  // Note the time the button was pressed
  if (buttonValue != CONTROLEO_BUTTON_NONE)
   lastChangeMillis = nowMillis;
  
  return buttonValue;
}

