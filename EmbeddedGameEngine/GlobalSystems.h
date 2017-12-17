#pragma once

/* only some forward declarations */
class OSDriver;
class MessageBus;
class DisplayDriver;
class InputDriver;
class SoundDriver;

/* get raw pointers to objects.. */
extern OSDriver* OS;
extern MessageBus* MsgBus;
extern DisplayDriver* displayDriver;
extern InputDriver* inputDriver;
extern SoundDriver* soundDriver;

/* Functions for settings these variables */
void SetOS(OSDriver* o);
void SetMsgBus(MessageBus* m);
void SetDisplayDriver(DisplayDriver* d);
void SetInputDriver(InputDriver* i);
void SetSoundDriver(SoundDriver* s);
