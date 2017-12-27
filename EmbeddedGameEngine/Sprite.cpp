#include "Sprite.h"
#include "lodepng.h"
#include <iostream>

Sprite::~Sprite()
{
	if(freeData && pixelData != NULL)
		free((void*)pixelData);
}

Sprite* Sprite::FromPNG(const char* path) {
	//Try to decode the given file in
	//RGBA format
	unsigned error;
	unsigned char* image;
	unsigned w = 0, h = 0;

	std::cout << "Loading PNG file " << path << std::endl;

	/* load the PNG in one function call*/
	error = lodepng_decode32_file(&image, &w, &h, path);

	/* stop if there is an error*/
	if(error)
	{
		printf("decoder error %u: %s\n", error, lodepng_error_text(error));
		return nullptr;
	}

	std::cout << "Loaded PNG " << path << " dim " << w << "," << h << std::endl;

	return new Sprite((const void*)image, (int)w, (int)h, ColorFormat::R8G8B8A8, true);
}

