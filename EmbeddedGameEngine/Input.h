#pragma once

#include "InputDriver.h"
#include "Gamepad.h"

#define INPUT_MAX_PLAYERS 4

class Input
{
private:
	static InputDriver* drivers[INPUT_MAX_PLAYERS];
	static GamePad gamepads[INPUT_MAX_PLAYERS];

public:

	static void RegisterInput(int player, InputDriver* driver) {
		if(player >= 0 && player < INPUT_MAX_PLAYERS)
			drivers[player] = driver;
	}

	static GamePad* GetGamepad(int player) {
		return &(gamepads[player]);
	}

	static void ReadInput() {
		InputDriver* driver = nullptr;
		for(int i=0; i < INPUT_MAX_PLAYERS; i++) {
			driver = drivers[i];
			if(driver) {
				driver->ReadInput(gamepads[i]);
			}
		}
	}

	Input();
	~Input();
};

