#pragma once
#include "DisplayDriver.h"
#include "SDL.h"

class SDLDisplayDriver :
	public DisplayDriver
{
public:
	SDLDisplayDriver();
	~SDLDisplayDriver();

	// Geerbt ueber DisplayDriver
	virtual Display DescribeDisplay() override;
	virtual bool Initialize() override;
	virtual void DrawFramebuffer() override;
	virtual void DrawBitmap(int x, int y, const uint8_t * data, int width, int height, ColorFormat source_format, BlendMode blend_mode) override;
	virtual void ClearFramebuffer() override;
	virtual void Destroy() override;

private:
	Display displayInfo;

	/* SDL specific stuff */
	SDL_Window *window;
	SDL_Renderer* Main_Renderer;
	SDL_Surface* Loading_Surf;
	SDL_Texture* ScreenTexture;

	int texturePitch;
	uint32_t format;
};

