#include <Adafruit_NeoPixel.h>

int const all_max = 255;
int const wh_ligmin = 0;
int const wh_ligmax = all_max;  //(0, 0, 0, lig)
int const red_ligmin = 0;
int const red_ligmax = all_max; //(lig, 0, 0, 0)
int const gr_ligmin = 0;
int const gr_ligmax = all_max;  //(0, lig, 0, 0)
int const bl_ligmin = 0;
int const bl_ligmax = all_max;  //(0, 0, lig, 0)

//int const receivedValue = 0

#define PIN 6        // Пин данных
#define NUMPIXELS 1  // Кол-во светодиодов

// GRBW — особый порядок, поддерживаемый этой моделью
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(960000);
  strip.begin();     
  strip.show();
}

void loop() {
  rgbw();
}

void rgbw(){
  if (Serial.available()) {
    int receivedValue = Serial.parseInt() * 2;
    if (receivedValue < 128){
    strip.setPixelColor(0, strip.Color(0, 0, 0, receivedValue)); // Только белый
    strip.show();
    }
    if (receivedValue > 127 and receivedValue < 256){
    strip.setPixelColor(0, strip.Color(0, 0, receivedValue - 128, 128)); // Белый + Синий
    strip.show();
    }
    if (receivedValue > 255 and receivedValue < 384){
    strip.setPixelColor(0, strip.Color(0, receivedValue - 128, 128, 128)); // Белый + Синий + Зеленый
    strip.show();
    }
    if (receivedValue > 383){
    strip.setPixelColor(0, strip.Color(receivedValue - 128, 128, 128, 128)); // Белый + Синий + Зеленый + Красный
    strip.show();
    }
  }
}

void only_w(){
  if (Serial.available()) {
    int receivedValue = Serial.parseInt();
    strip.setPixelColor(0, strip.Color(0, 0, 0, receivedValue)); // Только белый
    strip.show();
    }
}

