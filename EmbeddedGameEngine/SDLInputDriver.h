#pragma once

#include "InputDriver.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>

struct SDLKeyMap {
	int SDLKeys[NUM_GAMEPAD_BUTTONS];
	GamePadButton GamePadButtons[NUM_GAMEPAD_BUTTONS];
};


class SDLInputDriver : public InputDriver
{
public:

	const SDLKeyMap keymap = {
			/* 10 SDL keys */
			SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN,
			SDL_SCANCODE_A ,SDL_SCANCODE_B,
			SDL_SCANCODE_RETURN,SDL_SCANCODE_BACKSPACE,
			SDL_SCANCODE_J, SDL_SCANCODE_K,

			/* 10 gamebutton keys */
			GamePadButton::Left, GamePadButton::Right,
			GamePadButton::Up, GamePadButton::Down,
			GamePadButton::A, GamePadButton::B,
			GamePadButton::START, GamePadButton::SELECT,
			GamePadButton::LT, GamePadButton::RT
	};

	bool IsConnected() {
		return true;
	}

	void ReadInput(GamePad& gamePad) {
		//std::cout << "READING INPUT" << std::endl;
		//Update keyboard state
		SDL_PumpEvents();
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		for(int i=0; i < NUM_GAMEPAD_BUTTONS; i++) {
			if(keystate[keymap.SDLKeys[i]]) {
				//key is pressed
				//std::cout << "button pressed" << std::endl;
				gamePad.buttons[(int)keymap.GamePadButtons[i]] = true;
			} else {
				gamePad.buttons[(int)keymap.GamePadButtons[i]] = false;
			}
		}
	}


	SDLInputDriver();
	~SDLInputDriver();
};

