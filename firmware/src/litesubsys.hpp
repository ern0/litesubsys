# ifndef indicator_hpp
# define indicator_hpp

# define ONBOARD_PIN 13
# define POWER_PIN 4
# define LIGHT_PIN 9

# define POWER_BUTTON 1
# define LIGHT_BUTTON 0

enum {
	E_NONE = '-',
	E_POWER_OFF = 'p',
	E_POWER_ON = 'P',
	E_LIGHT_OFF = 'l',
	E_LIGHT_ON = 'L'
};

enum {
	ON,
	OFF
};

enum {
	KEY_PRESSED,
	KEY_RELEASED
};

inline void clearEvents();
inline void fire(char internalEvent,bool ext);
inline void confirmExternalEvent();
inline void pollSerial();
inline void pollButtons();
void pollButtonLogic(int pin,char* keyState,char opState,int onEvent,int offEvent);

inline void powerOn();
inline void powerOff();
inline void lightOn();
inline void lightOff();

# endif
