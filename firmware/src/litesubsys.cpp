# include "litesubsys.hpp"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1,LIGHT_PIN,NEO_GRB | NEO_KHZ800);

void setup() {

  pinMode(ONBOARD_PIN,OUTPUT);
  pinMode(POWER_PIN,OUTPUT);
  pinMode(LIGHT_PIN,OUTPUT);

  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(30);


} // setup()


void loop() {

  digitalWrite(ONBOARD_PIN,HIGH);
  digitalWrite(POWER_PIN,HIGH);
  strip.setPixelColor(0, 255,255,0);
  strip.show();
  delay(200);

  digitalWrite(ONBOARD_PIN,LOW);
  digitalWrite(POWER_PIN,LOW);
  strip.setPixelColor(0, 0,0,0);
  strip.show();
  delay(700);

} // loop()
