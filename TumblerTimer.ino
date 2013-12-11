#include <Wire.h>
#include <rtc_clock.h>
#include <Adafruit_RGBLCDShield.h>

   
// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
RTC_clock rtc_clock(XTAL);

// These #defines make it easy to set the backlight color
#define WHITE 0x7
#define OFF   0x0

int endTime1 = 0;
int endTime2 = 0;
int endTime3 = 0;
int endTime4 = 0;

const int relay1 = 8;
const int relay2 = 9;
const int relay3 = 10;
const int relay4 = 11;

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void) 
{

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.setBacklight(WHITE);
  
  rtc_clock.init();
  
  pinMode(relay1, OUTPUT);  
  pinMode(relay2, OUTPUT);      
  pinMode(relay3, OUTPUT);      
  pinMode(relay4, OUTPUT);      
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void) 
{
 
    uint8_t buttons = lcd.readButtons();
    lcd.setCursor(0,0);
    lcd.print("              ");
    lcd.setCursor(0,1);
    lcd.print("              ");

    if (buttons) {
      if (buttons & BUTTON_UP) {
        lcd.display();
        lcd.setBacklight(WHITE);
        if (endTime1 != 0) {
          timer1();
        } else {
          endTime1 = rtc_clock.unixtime() + 1200;
          digitalWrite(relay1, LOW);
        }
      }
      if (buttons & BUTTON_DOWN) {
        lcd.display();
        lcd.setBacklight(WHITE);
        if (endTime2 != 0) {
          timer2();
        } else {
          endTime2 = rtc_clock.unixtime() + 15;
          digitalWrite(relay2, LOW);
        }
      }
      if (buttons & BUTTON_LEFT) {
        lcd.display();
        lcd.setBacklight(WHITE);
        if (endTime3 != 0) {
          timer3();
        } else {
          endTime3 = rtc_clock.unixtime() + 14400;
          digitalWrite(relay3, LOW);
        }
      }
      if (buttons & BUTTON_RIGHT) {
        lcd.display();
        lcd.setBacklight(WHITE);
        if (endTime4 != 0) {
          timer4();
        } else {
          endTime4 = rtc_clock.unixtime() + 30;
          digitalWrite(relay4, LOW);
      }
      if (buttons & BUTTON_SELECT) {
        lcd.noDisplay();
        lcd.setBacklight(OFF);
      }
    }
  }
  lcd.setCursor(0,0);
  lcd.print("             ");
  lcd.setCursor(0,1);
  lcd.print("             ");

  if ( rtc_clock.unixtime() > endTime1 && endTime1 != 0 ) {
    timer1();
  } else if ( endTime1 - rtc_clock.unixtime() && endTime1 > 0 ) {
    lcd.setCursor(0,0);
    lcd.print(endTime1 - rtc_clock.unixtime());
  }
  if ( rtc_clock.unixtime() > endTime2 && endTime2 != 0 ) {
    timer2();
  } else if ( endTime2 - rtc_clock.unixtime() && endTime2 > 0 ) {
    lcd.setCursor(8,0);
    lcd.print(endTime2 - rtc_clock.unixtime());
  }
  if ( rtc_clock.unixtime() > endTime3 && endTime3 != 0 ) {
    timer3();
  } else if ( endTime3 - rtc_clock.unixtime() && endTime3 > 0 ) {
    lcd.setCursor(0,1);
    lcd.print(endTime3 - rtc_clock.unixtime());
  }
  if ( rtc_clock.unixtime() > endTime4 && endTime4 != 0 ) {
    timer4();
  } else if ( endTime4 - rtc_clock.unixtime() && endTime4 > 0 ) {
    lcd.setCursor(8,1);
    lcd.print(endTime4 - rtc_clock.unixtime());
  }

 
  delay(1000);
}

void timer1() {
  digitalWrite(relay1, HIGH);
  endTime1 = 0;
  lcd.setCursor(14,0);
  lcd.print(" ");
}
void timer2() {
  digitalWrite(relay2, HIGH);
  endTime2 = 0;
  lcd.setCursor(15,0);
  lcd.print(" ");
}
void timer3() {
  digitalWrite(relay3, HIGH);
  endTime3 = 0;
  lcd.setCursor(14,1);
  lcd.print(" ");
}
void timer4() {
  digitalWrite(relay4, HIGH);
  endTime4 = 0;
  lcd.setCursor(15,1);
  lcd.print(" ");
}
