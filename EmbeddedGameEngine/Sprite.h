#pragma once

#include "ColorFormat.h"
#include <cstdlib>

#define LAYERS_MAX 3

class Sprite
{
public:

	static Sprite* FromPNG(const char* path);

	Sprite(const void* pixelData, int width, int height,
	ColorFormat colorFormat, bool free=false) :
		pixelData(pixelData), width(width), height(height),
		colorFormat(colorFormat), freeData(free){ }

	/* Memory management? who deallocates sprite data? */
	~Sprite();

	const void* GetPixelData() { return pixelData; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	ColorFormat GetColorFormat() { return colorFormat; }

private:
	const void* pixelData;
	int width, height;
	ColorFormat colorFormat;
	bool freeData;
};

