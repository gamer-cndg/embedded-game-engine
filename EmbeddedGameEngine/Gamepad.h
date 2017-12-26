#pragma once

#include "Vector2.hpp"

#define NUM_GAMEPAD_BUTTONS 10

enum class GamePadButton {
	Left = 0, Right, Up, Down,
	A, B,
	START, SELECT,
	LT, RT
};

class GamePad {
public:

	bool IsButtonDown(GamePadButton btn) {
		return buttons[(int)btn];
	}

	bool IsButtonUp(GamePadButton btn) {
		return !buttons[(int)btn];
	}

	Vector2 ReadMovement() {
		float x = 0;
		float y = 0;
		if(buttons[(int)GamePadButton::Left])
			x -= 1.0f;
		if(buttons[(int)GamePadButton::Right])
			x += 1.0f;
		if(buttons[(int)GamePadButton::Up])
			y -= 1.0f;
		if(buttons[(int)GamePadButton::Down])
			y += 1.0f;

		return Vector2(x, y);
	}

	bool buttons[NUM_GAMEPAD_BUTTONS];

	GamePad();
	~GamePad();
};

