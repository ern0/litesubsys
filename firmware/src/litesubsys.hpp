# ifndef indicator_hpp
# define indicator_hpp

# define ONBOARD_PIN 13
# define POWER_PIN 4
# define LIGHT_PIN 9

# define POWER_BUTTON 1
# define LIGHT_BUTTON 0

# define APP_SIGNATURE "LiTe"

enum {
	E_NONE = '-',
	E_POWER_OFF = 'p',
	E_POWER_ON = 'P',
	E_LIGHT_OFF = 'l',
	E_LIGHT_ON = 'L',
	E_ABOUT = '\b'
};

enum {
	ON,
	OFF
};

enum {
	KEY_PRESSED,
	KEY_RELEASED
};

enum {
	SHOW_UNDEF,
	SHOW_OFF,
	SHOW_ON,
	SHOW_LIT
};

inline void about();
inline void initVars();
inline void clearEvents();
inline void fire(char internalEvent,bool ext);
inline void confirmExternalEvent();
inline void pollSerial();
inline void pollButtons();
void pollButtonLogic(int pin,char* keyState,char opState,int onEvent,int offEvent,int* muteCounter);

inline void powerOn();
inline void powerOff();
inline void lightOn();
inline void lightOff();

inline void show();
inline void showAdmin();
inline void showOnboard();
inline void showLight();

# endif
