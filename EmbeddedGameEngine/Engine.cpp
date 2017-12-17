#include "Engine.h"

void Engine::Start()
{
	displayDriver->Initialize();

	//Start draw thread
	//Start sound thread
	//Start Script thread..
}

void Engine::Stop()
{
	displayDriver->Destroy();
}


Engine::Engine(OSDriver * os, DisplayDriver * display, InputDriver * input, SoundDriver * sound)
{
	SetMsgBus(&mbus);
	SetDisplayDriver(display);
	SetInputDriver(input);
	SetSoundDriver(sound);
}

Engine::~Engine()
{
}
