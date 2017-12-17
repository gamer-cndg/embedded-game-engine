#include <iostream>
#include <SDL.h>
#include "Engine.h"

/* Include platform specific implementations */
#include "WindowsOSDriver.h"
#include "SDLDisplayDriver.h"
#include "SDLInputDriver.h"
#include "SDLSoundDriver.h"

WindowsOSDriver osDriver;
SDLDisplayDriver sdlDisplayDriver;
SDLInputDriver sdlInputDriver;
SDLSoundDriver sdlSoundDriver;

Engine engine(
	(OSDriver*)&osDriver, 
	(DisplayDriver*)&sdlDisplayDriver, 
	(InputDriver*)&sdlInputDriver, 
	(SoundDriver*)&sdlSoundDriver
);

//left side
uint32_t myRect[800 * 300 ] = { 0 };
//right side
uint32_t myRect2[800 * 300] = { 0 };

void writeTexture(uint8_t* texture, size_t numBytes, uint8_t r, uint8_t g, uint8_t b) {
	for (int i = 0; i < sizeof(myRect); i += 4) {
		texture[i]		= r; //R
		texture[i + 1]	= g; //G
		texture[i + 2]	= b; //B
		texture[i + 3]	= 0; //A
	}
}
int main(int argc, char *argv[]) {

	writeTexture((uint8_t*)myRect, sizeof(myRect), 0xff, 0x00, 0x00);
	writeTexture((uint8_t*)myRect2, sizeof(myRect2), 0xab, 0x00, 0xbc);

	engine.Start();

	//Draw both textures
	sdlDisplayDriver.DrawBitmap(0, 0, (uint8_t*)myRect, 800, 300, ColorFormat::R8G8B8A8, BlendMode::Overwrite);
	sdlDisplayDriver.DrawBitmap(0, 300, (uint8_t*)myRect2, 800, 300, ColorFormat::R8G8B8A8, BlendMode::Overwrite);

	SDL_Event evt;
	for (int i = 0; i < 50; i++) {
		sdlDisplayDriver.DrawFramebuffer();
		SDL_PollEvent(&evt);
		Sleep(100);
	}

	engine.Stop();

	return 0;
}