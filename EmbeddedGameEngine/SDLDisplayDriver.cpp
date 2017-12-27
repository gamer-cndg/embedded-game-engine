#include "SDLDisplayDriver.h"
#include <string>
#include <iostream>
#include <stdio.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240
//#define DISPLAY_WIDTH 600
//#define DISPLAY_HEIGHT 480

static inline bool CheckSDL(int expr, std::string err)  {
	if( (expr) != 0) { 
		std::cerr << err << "failed!" << std::endl; 
		std::cerr << SDL_GetError() << std::endl; 
		return false;
	}
	return true;
}

SDLDisplayDriver::SDLDisplayDriver()
{
	displayInfo.color_format = ColorFormat::R8G8B8;
	displayInfo.width = DISPLAY_WIDTH;
	displayInfo.height = DISPLAY_HEIGHT;
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
	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

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
			//SDL_PIXELFORMAT_ARGB8888,
			//SDL_PIXELFORMAT_ABGR32,
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

/* alpha blend routine */
inline unsigned int AlphaBlend(const unsigned int bg, const unsigned int src)
{
	unsigned int a = src >> 24;    /* alpha */

	/* If source pixel is transparent, just return the background */
	if (0 == a)
		return bg;

	/* alpha blending the source and background colors */
	unsigned int rb = (((src & 0x00ff00ff) * a) +
		((bg & 0x00ff00ff) * (0xff - a))) & 0xff00ff00;
	unsigned int    g  = (((src & 0x0000ff00) * a) +
		((bg & 0x0000ff00) * (0xff - a))) & 0x00ff0000;

	return (src & 0xff000000) | ((rb | g) >> 8);
}

void blendcpy(void* dest, void* src, size_t numBytes) {
	uint32_t* pSrc = (uint32_t*) src;
	uint32_t* pDst = (uint32_t*) dest;
	int i = 0;
	while(numBytes > 0) {
		pDst[i] = AlphaBlend(pDst[i], pSrc[i]);
		i++;
		numBytes -= 4;
	}
}

void SDLDisplayDriver::DrawBitmap(int x, int y, const uint8_t * data, int width, int height, ColorFormat source_format, BlendMode blend_mode)
{
	/* alternative method using locking textures */

	//Which part of the texture to we have to update?

	//from source image
	int srcX = 0, srcY = 0;

	//for destination texture

	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = width;
	r.h = height;

	//std::cout << "original (x,y,w,h) = " << r.x << "," << r.y << "," << r.w <<","<<r.h << std::endl;

	/*if(r.x + r.w < 0 && r.y + r.h < 0) {
		//not on the left side of the screen
		return;
	}*/

	//clipping
	if(r.x + r.w > DISPLAY_WIDTH) {
		r.w = DISPLAY_WIDTH - r.x;
	}

	if(r.y + r.h > DISPLAY_HEIGHT) {
		r.h = DISPLAY_HEIGHT - r.y;
	}
	if(r.x < 0) { r.w += r.x; srcX = -r.x; r.x = 0;  }
	if(r.y < 0) { r.h += r.y; srcY = -r.y; r.y = 0; }


	//std::cout << "(x,y,w,h) = " << r.x << "," << r.y << "," << r.w <<","<<r.h << std::endl;
	//std::cout << "texture pitch: " << texturePitch << std::endl;
	/*CheckSDL(SDL_UpdateTexture(ScreenTexture, &r, data, 4 * width ), "UpdateTexture");
	*/

	uint32_t* pRGB = (uint32_t*) lockedPixels;
	uint32_t* pD2 = (uint32_t*) data;
	int savedStart = srcX;
//#pragma omp parallel for
	for(int curY = r.y; curY < r.y + r.h; curY++) {
		srcX = savedStart;

		uint32_t pixelPos = curY * DISPLAY_WIDTH + r.x;
		size_t numPixels = (r.w) * 4;
		uint32_t srcPos = srcY * width + srcX;

		//copy the entire row into the framebuffer..
		blendcpy(&pRGB[pixelPos], &pD2[srcPos], numPixels);
		srcX += r.w;

		/*for(int curX = r.x; curX < r.x + r.w; curX++) {
			uint32_t pixelPos = curY * DISPLAY_WIDTH + curX;
			uint32_t srcPos = srcY * width + srcX;

			uint32_t srcPixel = ((uint32_t*)data)[srcPos];

			uint32_t convertedPixel = le32toh(srcPixel);

#if 0
			std::cout
				<< "Copy from src " << srcX << "," << srcY
				<< " to dest " << curX << "," << curY
				<< " src pos " << srcPos << " dest pos " << pixelPos
				<< " pitch " << pitch;
			//	<< std::endl;

			std::cout.flush();
			printf(" pixel %08x\n", srcPixel);
#endif

			pRGB[pixelPos] = convertedPixel;
			srcX++;
		}*/
		srcY++;
	}

	SDL_UnlockTexture(ScreenTexture);
}

void SDLDisplayDriver::ClearFramebuffer()
{
	/*void* pixels;
	int pitch;
	//Try to lock the entire screen texture
	if(!CheckSDL(SDL_LockTexture(ScreenTexture, NULL, &pixels, &pitch),"Locktexture")) {
		return;
	}*/
	memset(lockedPixels, 0x00, DISPLAY_WIDTH * lockedPitch);
	//SDL_UnlockTexture(ScreenTexture);
	//SDL_RenderClear(Main_Renderer);
}


#include <iostream>

void SDLDisplayDriver::Destroy()
{

	std::cout << "Destroying window now " << std::endl;

	// Close and destroy the window
	SDL_DestroyTexture(ScreenTexture);
	SDL_DestroyRenderer(Main_Renderer);
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
}

void SDLDisplayDriver::BeginDraw() {
	void* pixels;
	int pitch;

	//Try to lock the entire screen texture
	if(!CheckSDL(SDL_LockTexture(ScreenTexture, NULL, &pixels, &pitch),"Locktexture")) {
		return;
	}

	lockedPixels = pixels;
	lockedPitch = pitch;
}

void SDLDisplayDriver::EndDraw() {
	SDL_UnlockTexture(ScreenTexture);
}
