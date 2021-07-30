#include <Arduino.h>
#include <Watchy.h>
#include "OverpassMono_Bold12pt7b.h"
#include "OverpassMono_Bold50pt7b.h"
				

class WatchFace : public Watchy {
  public:
    void drawWatchFace() {
      
      int16_t  x1, y1;
      uint16_t w, h;
      String textstring;

      WiFi.mode(WIFI_OFF);
      btStop();
   
      if(currentTime.Hour == 0 && currentTime.Minute == 0) {
        sensor.resetStepCounter(); 
        vibMotor(100, 2);
        delay(50);
        vibMotor(100, 2);
      }
      
      display.setTextColor(GxEPD_BLACK);
      display.fillScreen(GxEPD_WHITE);
      display.setTextWrap(false);
      display.setFont(&OverpassMono_Bold50pt7b);


      textstring = currentTime.Hour;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(185-w, 85-5);
      display.print(textstring);
      

      if (currentTime.Minute < 10) {
        textstring = "0";
      } else {
        textstring = "";
      }
      textstring += currentTime.Minute;
      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(185-w, 90-5+h);
      display.print(textstring);

      display.setFont(&OverpassMono_Bold12pt7b);

      const float MAX_BATT = 4.23;
      const float MIN_BATT =  3.3;

      float batt = getBatteryVoltage();
      float batt_percentage = ((batt - MIN_BATT) * 100) / (MAX_BATT - MIN_BATT);

      display.setCursor(1, 17);
      display.printf("%0.0f%%\n", batt_percentage);
      display.setCursor(1, 36);
      display.print(batt);

      textstring = dayShortStr(currentTime.Wday);
      textstring += " ";
      textstring += currentTime.Day;
      textstring += " ";
      textstring += monthShortStr(currentTime.Month);

      display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
      display.setCursor(1, 199);
      display.print(textstring);
    }
};

WatchFace m;

void setup() {
  m.init();
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
