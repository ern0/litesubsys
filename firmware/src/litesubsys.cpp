# include "litesubsys.hpp"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1,LIGHT_PIN,NEO_GRB | NEO_KHZ800);
static char powerState = OFF;
static char lightState = OFF;
static char singleElemEventBuffer;


void setup() {

  pinMode(ONBOARD_PIN,OUTPUT);
  pinMode(POWER_PIN,OUTPUT);
  pinMode(LIGHT_PIN,OUTPUT);

  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(30);

	powerOff();
	lightOff();

} // setup()


void loop() {

	clearEvent();

	pollSerial();
	pollButtons();

	switch (singleElemEventBuffer) {
	case E_POWER_ON:
		powerOn();
		break;
	case E_POWER_OFF:
		powerOff();
		break;
	case E_LIGHT_ON:
		lightOn();
		break;
	case E_LIGHT_OFF:
		lightOff();
		break;
	}

  delay(100);

} // loop()


inline void clearEvent() {
	singleElemEventBuffer = E_NONE;
} // clearEvent()


inline void fire(char event) {
	singleElemEventBuffer = event;
} // fire()



inline void pollSerial() {

  char c = Serial.read();

  if (c == 'p') fire(E_POWER_OFF);
  if (c == 'P') fire(E_POWER_ON);
  if (c == 'l') fire(E_LIGHT_OFF);
  if (c == 'L') fire(E_LIGHT_ON);

} // pollSerial()


inline void pollButtons() {

	/// TODO

} // pollButtons()


inline void powerOn() {

	digitalWrite(POWER_PIN,HIGH);
	powerState = ON;

} // powerOn()


void powerOff() {

	digitalWrite(POWER_PIN,LOW);
	lightOff();
	powerState = OFF;

} // powerOff()


inline void lightOn() {

	if (powerState == OFF) return;

	strip.setPixelColor(0, 255,40,0);
	strip.show();
	lightState = ON;

} // lightOn()


inline void lightOff() {

	strip.setPixelColor(0, 0,0,0);
	strip.show();
	lightState = OFF;

} // lightOff()
