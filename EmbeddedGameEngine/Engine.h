#pragma once

#include "GFX.h"
#include "Sound.h"
#include "Input.h"
#include "DisplayDriver.h"
#include "InputDriver.h"
#include "SoundDriver.h"
#include "MessageBus.h"
#include "OSDriver.h"
#include "Scene.h"
#include "SceneManager.h"

class Engine
{
public:

	void Start();
	void Stop();

	Engine(OSDriver* os, DisplayDriver* display, InputDriver* input, SoundDriver* sound);
	~Engine();
private:
	MessageBus mbus;
	GFX gfx;

	OS_TaskHandle gfxThread;
};

