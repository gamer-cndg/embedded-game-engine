#pragma once

#include <stdint.h>
#include "ColorFormat.h"

/* Describes the blending modes */
enum class BlendMode { Overwrite, Add, Subtract, Multiply  };

/* Describes a display */
struct Display {
	int width, height;
	ColorFormat color_format;
	int maxFPS;
};

/* Describes the capabilies of a display driver. Is an abstract class. Must be implemented by some implementation */
class DisplayDriver
{
public:
	/* get the capabilities of the display */
	virtual Display DescribeDisplay() = 0;

	/* Initialize the display */
	virtual bool Initialize() = 0;

	/* destroy the display */
	virtual void Destroy() = 0;

	/* Draw current framebuffer */
	virtual void DrawFramebuffer() = 0; 

	/* methods which lock/unlock the screen if necessary. */
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;

	/* Manipulate frame buffer methods */

	/* Draw bitmap at (x,y) of dimensions width x height from the graphics data pointed to by data with given blend mode */
	virtual void DrawBitmap(int x, int y, const uint8_t* data, int width, int height, ColorFormat source_format, BlendMode blend_mode) = 0;

	/* delete all contents in the framebuffer */
	virtual void ClearFramebuffer() = 0;

	DisplayDriver() {}
	~DisplayDriver() {}
private:
};
