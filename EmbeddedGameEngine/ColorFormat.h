/*
 * ColorFormat.h
 *
 *  Created on: 25-Dec-2017
 *      Author: pi
 */

#ifndef COLORFORMAT_H_
#define COLORFORMAT_H_

#include <stdint.h>
#include <stddef.h>

/* Describes the possible color formats */
enum class ColorFormat { R8G8B8, R8G8B8A8 };

class ColorHelper {
public:
	/* Returns number of bytes given width, height and color format. */
	static size_t ByteLength(ColorFormat c, int width, int height) {
		int factor = 1;
		switch(c) {
		case ColorFormat::R8G8B8: factor = 3; break;
		case ColorFormat::R8G8B8A8: factor = 4; break;
		default: factor = 0; break;
		}
		return (size_t)(factor * width * height);
	}
};


#endif /* COLORFORMAT_H_ */
