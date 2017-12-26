#include "Engine.h"

void Engine::Start()
{
	displayDriver->Initialize();

	//init input
	//test: register input driver for player 0
	Input::RegisterInput(0, inputDriver);

	//Start draw thread
	gfx.Init();
	OS->NewThread((void*) GFX::GFXThread, "gfx", 1024, NULL, 1, gfxThread);

	//Start sound thread

	//Start Script thread..

	//Start scenen initialization?!
}

void Engine::Stop()
{
	GFX::stopGFX = true;
	OS->Sleep(1000);
	displayDriver->Destroy();
	//TODO: unload scene, sprites,...
}

Engine::Engine(OSDriver * os, DisplayDriver * display, InputDriver * input, SoundDriver * sound)
{
	SetMsgBus(&mbus);
	SetOS(os);
	SetDisplayDriver(display);
	SetInputDriver(input);
	SetSoundDriver(sound);
}

Engine::~Engine()
{
}
