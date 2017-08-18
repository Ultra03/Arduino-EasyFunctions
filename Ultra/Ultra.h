#ifndef Ultra_h
#define Ultra_h
#include "Arduino.h"

class Ultra {
public:
	Ultra();
	void startup();
	void freeflyLoop();
	void passwordInput();

private:
	int temp[4];
	int password[4];
	int index;
	int tries;
};

#endif