#include "GlobalSystems.h"

OSDriver* OS = nullptr;
MessageBus* MsgBus = nullptr;
DisplayDriver* displayDriver = nullptr;
InputDriver* inputDriver = nullptr;
SoundDriver* soundDriver = nullptr;

void SetOS(OSDriver* o) {
	OS = o;
}

void SetMsgBus(MessageBus* m) {
	MsgBus = m;
}

void SetDisplayDriver(DisplayDriver* d) {
	displayDriver = d;
}
void SetInputDriver(InputDriver* i) {
	inputDriver = i;
}

void SetSoundDriver(SoundDriver* s) {
	soundDriver = s;
}
