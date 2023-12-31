#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

const unsigned PHOTORESISTOR = 0;

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void setup(void) {
  Serial.begin(9600);

  u8g2.begin();
}

void loop(void) {
  unsigned photoresistor_value = analogRead(PHOTORESISTOR);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.setCursor(0, 15);
    u8g2.print("Hello World! \n");

    u8g2.setCursor(0, 31);
    u8g2.print(photoresistor_value);

    u8g2.display();
  } while ( u8g2.nextPage() );
  delay(1000);
}
