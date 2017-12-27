#pragma once

#include "Vector2.hpp"

/* The camera usually has more sophisticated stuff
 * like view frustum, zoom, etc..
 * For our engine, a camera is just a point
 * in the world. The "eye" vector.
 * Adding zooming features or multiple
 * viewpoints would eat up too much CPU.
 *  */
class Camera
{
public:

	static Vector2 position;

	Camera();
	~Camera();
};

