# include "litesubsys.hpp"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1,LIGHT_PIN,NEO_GRB | NEO_KHZ800);

static char powerState = OFF;
static char lightState = OFF;
static char powerButtonState = KEY_RELEASED;
static char lightButtonState = KEY_RELEASED;

static char internalEventBuffer;
static char externalEventBuffer;
static bool externalEventTransmit;

static char actualShow;
static char lastShow;
static int onboardCounter;
static int lightCounter;


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

	actualShow = SHOW_UNDEF;
	lastShow = SHOW_UNDEF;
	onboardCounter = 0;
	lightCounter = 0;

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

	show();

  delay(20);

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

	lightState = ON;
	confirmExternalEvent();

} // lightOn()


inline void lightOff() {

	strip.setPixelColor(0, 0,0,0);
	strip.show();
	lightState = OFF;
	confirmExternalEvent();

} // lightOff()


inline void show() {

	showAdmin();
	showOnboard();
	showLight();

} // show()


inline void showAdmin() {

	if (powerState == OFF) {
		actualShow = SHOW_OFF;
	} else if (lightState == OFF) {
		actualShow = SHOW_ON;
	} else {
		actualShow = SHOW_LIT;
	}

	if (actualShow != lastShow) {

		lastShow = actualShow;
		onboardCounter = 0;
		lightCounter = 0;

	} // if show change

} // showAdmin()


inline void showOnboard() {

	int v = LOW;

	switch (actualShow) {
	case SHOW_OFF:
		if (onboardCounter > 30) v = HIGH;
		break;
	case SHOW_ON:
		if (onboardCounter > 4) v = HIGH;
		break;
	case SHOW_LIT:
		if (onboardCounter % 16 < 3) v = HIGH;
		break;
	}

	digitalWrite(ONBOARD_PIN,v);

	onboardCounter++;
	if (onboardCounter > 32) onboardCounter = 0;

} // showOnboard()


inline void showLight() {

	switch (actualShow) {
	case SHOW_OFF:
	case SHOW_ON:
		strip.setPixelColor(0, 0,0,0);
		strip.show();
		break;
	case SHOW_LIT:

		int index = lightCounter / 64;
		if (index == 0) strip.setPixelColor(0, 255,128,0);
		if (index == 1) strip.setPixelColor(0, 32,32,255);
		if (index == 2) strip.setPixelColor(0, 0,255,64);
		if (index == 3) strip.setPixelColor(0, 64,255,0);
		strip.show();

		break;
	}

	lightCounter++;
	if (lightCounter > 256) lightCounter = 0;

} // showLight()
