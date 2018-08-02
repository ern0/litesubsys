# ifndef indicator_hpp
# define indicator_hpp

# define ONBOARD_PIN 13
# define POWER_PIN 4
# define LIGHT_PIN 9

# define POWER_BUTTON 6
# define LIGHT_BUTTON 7

enum {
	E_NONE,
	E_POWER_OFF,
	E_POWER_ON,
	E_LIGHT_OFF,
	E_LIGHT_ON
};

enum {
	ON,
	OFF
};

inline void clearEvent();
inline void fire(char event);
inline void pollSerial();
inline void pollButtons();

inline void powerOn();
inline void powerOff();
inline void lightOn();
inline void lightOff();

# endif
