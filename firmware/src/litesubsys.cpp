# include "litesubsys.hpp"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1,LIGHT_PIN,NEO_GRB | NEO_KHZ800);

void setup() {

  pinMode(INFO_PIN,OUTPUT);
  pinMode(POWER_PIN,OUTPUT);
  pinMode(LIGHT_PIN,OUTPUT);

  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(30);


} // setup()


void loop() {

  digitalWrite(INFO_PIN,HIGH);
  delay(200);
  digitalWrite(INFO_PIN,LOW);
  delay(200);

} // loop()
