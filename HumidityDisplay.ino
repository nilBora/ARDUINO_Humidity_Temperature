#include "DHT.h"
#include <iarduino_OLED_txt.h>                         
iarduino_OLED_txt myOLED(0x78);                        // Объявляем объект myOLED, указывая адрес дисплея на шине I2C: 0x78 (если учитывать бит RW=0).
                                                       
#define DHT21PIN 2
#define DHT11PIN 3
#define DHT21TYPE DHT21
#define DHT11TYPE DHT11

DHT dht11(DHT11PIN, DHT11);
DHT dht21(DHT21PIN, DHT21);

extern uint8_t SmallFontRus[];                         // Подключаем шрифт SmallFontRus.
                                                       //
void setup(){                                          //
    Serial.begin(9600);
    dht21.begin();
    dht11.begin();
    myOLED.begin();                                    // Инициируем работу с дисплеем.
    myOLED.setFont(SmallFontRus);                      // Указываем шрифт который требуется использовать для вывода цифр и текста.
//  myOLED.setCoding(TXT_UTF8);                        // Указываем кодировку текста в скетче. Если на дисплее не отображается Русский алфавит, то ...
}                                                      // раскомментируйте функцию setCoding и замените параметр TXT_UTF8, на TXT_CP866 или TXT_WIN1251.
                                                       //
void loop(){                                           //
    myOLED.clrScr();                                   

    float h21 = getHumidity(DHT21);
    float h11 = getHumidity(DHT11);
    
    float t21 = getTemperature(DHT21);
    float t11 = getTemperature(DHT11);
    
    if (isnan(h21) || isnan(t21)) {
      Serial.println("Ошибка считывания DHT21");
      return;
    }
    myOLED.print("DHT21", OLED_C, 0);
    myOLED.print("Влажность: ", 0, 1);
    myOLED.print(h21, 11, 1);
    myOLED.print("%", 15, 1);
    myOLED.print("Температура: ", 0, 2);
    myOLED.print(t21, 13, 2);
    myOLED.print("*C ", 16, 2);
    
    myOLED.print("DHT11", OLED_C, 4);
    myOLED.print("Влажность: ", 0, 5);
    myOLED.print(h21, 11, 5);
    myOLED.print("%", 15, 5);
    myOLED.print("Температура: ", 0, 6);
    myOLED.print(t21, 13, 6);
    myOLED.print("*C ", 16, 6);
    delay(5000); 
}

float getHumidity(int type)
{
  float h = 0.0;
  
  if (isDht21Type(type)) {
    h = dht21.readHumidity();
  }

  if (isDht11Type(type)) {
    h = dht11.readHumidity();
  }

  return h;
}

float getTemperature(int type)
{
  float t = 0.0;
  
  if (isDht21Type(type)) {
    t = dht21.readTemperature();
  }

  if (isDht11Type(type)) {
    t = dht11.readTemperature();
  }

  return t;
}

bool isDht21Type(int type)
{
  return type == DHT21;
}

bool isDht11Type(int type)
{
  return type == DHT11;
}
