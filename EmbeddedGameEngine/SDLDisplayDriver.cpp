#include "SDLDisplayDriver.h"
#include <string>
#include <iostream>
#include <stdio.h>

static inline void CheckSDL(int expr, std::string err)  {
	if( (expr) != 0) { 
		std::cerr << err << "failed!" << std::endl; 
		std::cerr << SDL_GetError() << std::endl; 
	}
}
SDLDisplayDriver::SDLDisplayDriver()
{
	displayInfo.color_format = ColorFormat::R8G8B8;
	displayInfo.width = 800;
	displayInfo.height = 600;
	displayInfo.maxFPS = 60;
}

SDLDisplayDriver::~SDLDisplayDriver()
{
}

Display SDLDisplayDriver::DescribeDisplay()
{
	return displayInfo;
}

bool SDLDisplayDriver::Initialize()
{
	//Init Window
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"GameEngine",						// window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		displayInfo.width,                 // width, in pixels
		displayInfo.height,                // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer
	Main_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Create 1 texture which will be our entire screen content
	ScreenTexture = 
		SDL_CreateTexture(
			Main_Renderer, 
			//SDL_PIXELFORMAT_RGBA8888, 
			SDL_PIXELFORMAT_ABGR8888,
			SDL_TEXTUREACCESS_STREAMING, 
			displayInfo.width, displayInfo.height);

	//query pitch etc from the texture
	int w, h;
	uint32_t* pixels;
	SDL_QueryTexture(ScreenTexture, &format, nullptr, &w, &h);
	if (SDL_LockTexture(ScreenTexture, nullptr, (void**)&pixels, &texturePitch))
	{
		std::cerr << "Locking texture failed!" << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}
	SDL_UnlockTexture(ScreenTexture);

	// The window is open: could enter program loop here (see SDL_PollEvent())
	return true;
}

void SDLDisplayDriver::DrawFramebuffer()
{
	SDL_RenderClear(Main_Renderer);

	if (SDL_RenderCopy(Main_Renderer, ScreenTexture, NULL, NULL) != 0) {
		std::cerr << "Drawing texture failed!" << std::endl;
		std::cerr << SDL_GetError() << std::endl;
	}
	SDL_RenderPresent(Main_Renderer);
}

void SDLDisplayDriver::DrawBitmap(int x, int y, uint8_t * data, int width, int height, ColorFormat source_format, BlendMode blend_mode)
{
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = width;
	r.h = height;
	std::cout << "texture pitch: " << texturePitch << std::endl;
	CheckSDL(SDL_UpdateTexture(ScreenTexture, &r, data, 4 * width ), "UpdateTexture");
}

void SDLDisplayDriver::ClearFramebuffer()
{
}

void SDLDisplayDriver::Destroy()
{
	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
}
