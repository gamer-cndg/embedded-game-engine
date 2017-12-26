#pragma once

#include "Gamepad.h"

class InputDriver
{
public:

	virtual bool IsConnected() = 0;
	virtual void ReadInput(GamePad& gamePad) = 0;

	InputDriver();
	~InputDriver();
};

