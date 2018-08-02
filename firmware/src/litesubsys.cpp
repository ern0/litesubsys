# include "litesubsys.hpp"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1,LIGHT_PIN,NEO_GRB | NEO_KHZ800);

static char powerState = OFF;
static char lightState = OFF;
static char powerButtonState = KEY_RELEASED;
static char lightButtonState = KEY_RELEASED;

static char internalEventBuffer;
static char externalEventBuffer;
bool externalEventTransmit;


void setup() {

  pinMode(ONBOARD_PIN,OUTPUT);
  pinMode(POWER_PIN,OUTPUT);
  pinMode(LIGHT_PIN,OUTPUT);

	pinMode(POWER_BUTTON,INPUT_PULLUP);
	pinMode(LIGHT_BUTTON,INPUT_PULLUP);

  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(30);

	powerOff();
	lightOff();

} // setup()


void loop() {

	clearEvents();

	pollSerial();
	pollButtons();

	switch (internalEventBuffer) {
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

	if (externalEventTransmit) {
		Serial.write(externalEventBuffer);
	}

  delay(100);

} // loop()


inline void clearEvents() {

	internalEventBuffer = E_NONE;
	externalEventBuffer = E_NONE;
	externalEventTransmit = false;

} // clearEvents()


inline void fire(char event,bool ext) {

	internalEventBuffer = event;
	if (ext) externalEventBuffer = event;

} // fire()


inline void confirmExternalEvent() {

	if (externalEventBuffer == E_NONE) return;
	externalEventTransmit = true;

} // confirmExternalEvent()


inline void pollSerial() {

  char event = Serial.read();

	bool valid = false;
  if (event == E_POWER_ON) valid = true;
	if (event == E_POWER_OFF) valid = true;
	if (event == E_LIGHT_OFF) valid = true;
	if (event == E_LIGHT_ON) valid = true;

	if (valid) fire(event,false);

} // pollSerial()


inline void pollButtons() {

	pollButtonLogic(
		POWER_BUTTON,
		&powerButtonState,
		powerState,
		E_POWER_ON,
		E_POWER_OFF
	);

	pollButtonLogic(
		LIGHT_BUTTON,
		&lightButtonState,
		lightState,
		E_LIGHT_ON,
		E_LIGHT_OFF
	);

} // pollButtons()


void pollButtonLogic(int pin,char* lastKeyState,char opState,int onEvent,int offEvent) {

	int v = analogRead(pin);
	char keyState = ( v == 0 ? KEY_PRESSED : KEY_RELEASED );
	if (keyState == *lastKeyState) return;
	*lastKeyState = keyState;

	if (keyState == KEY_RELEASED) return;

	fire(( opState == OFF ? onEvent : offEvent ),true);

} // pollButtonLogic()


inline void powerOn() {

	digitalWrite(POWER_PIN,HIGH);
	powerState = ON;
	confirmExternalEvent();

} // powerOn()


void powerOff() {

	digitalWrite(POWER_PIN,LOW);
	lightOff();
	powerState = OFF;
	confirmExternalEvent();

} // powerOff()


inline void lightOn() {

	if (powerState == OFF) return;

	strip.setPixelColor(0, 255,40,0);
	strip.show();
	lightState = ON;
	confirmExternalEvent();

} // lightOn()


inline void lightOff() {

	strip.setPixelColor(0, 0,0,0);
	strip.show();
	lightState = OFF;
	confirmExternalEvent();

} // lightOff()
