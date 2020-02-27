#include "DHT.h"
//url https://www.studiopieters.nl/attiny85-oled-i2c/
//ATTINY85  SDA - 0; SCK - 2 

#include <Tiny4kOLED.h>
                                                       
#define DHT21PIN 2
#define DHT11PIN 3
#define DHT21TYPE DHT21
#define DHT11TYPE DHT11

DHT dht11(DHT11PIN, DHT11);
DHT dht21(DHT21PIN, DHT21);

void setup()
{                                          
    dht21.begin();
    dht11.begin();
    oled.begin();                                    // Инициируем работу с дисплеем.
    oled.setFont(FONT8X16);
    oled.clear();
    oled.on();
    oled.switchRenderFrame();
} // end setup                                         
                                                  
void loop()
{                                           //
    oled.clear();
    // The characters in the 8x16 font are 8 pixels wide and 16 pixels tall
    // 2 lines of 16 characters exactly fills 128x32
                                   
    // Display Data DHT21 sensor
    float h21 = dht21.readHumidity();
    float t21 = dht21.readTemperature();

    oled.setCursor(0, 1);
    if (!isnan(h21) && !isnan(t21)) {
      oled.print("(DHT21) ");
      oled.print("H: ");
      oled.print(h21);
      oled.print("%; ");
      oled.print("T: ");
      oled.print(t21);
      oled.print("*C");
    } else {
      oled.print("DHT21 NOT FOUND");
    }

    // Display Data DHT11 sensor
    float h11 = dht11.readHumidity();
    float t11 = dht11.readTemperature();

    oled.setCursor(0, 2);
    if (!isnan(h11) && !isnan(t21)) {
      oled.print("(DHT21) ");
      oled.print("H: ");
      oled.print(h11);
      oled.print("%; ");
      oled.print("T: ");
      oled.print(t11);
      oled.print("*C ");
    } else {
      oled.print("DHT21 NOT FOUND");
    }

    oled.switchFrame();
    delay(5000); 
} // end loop
