/*
 * Animation.h
 *
 *  Created on: 27-Dec-2017
 *      Author: pi
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#define MAX_SPRITE_FRAMES 12
#include "Sprite.h"
#include "Time.h"
#include <vector>
#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>

/* A animation is a collection of sprite IDs */
class Animation {
public:

	//Empty constructor..
	Animation() { }

	Animation(std::vector<int> spriteIDs2, float time=1.0f, bool repeat=true)
	: timeBetweenFrames(time), repeat(repeat) {
		if(spriteIDs2.size() > MAX_SPRITE_FRAMES) throw new std::exception();
		int i = 0;
		for(int s : spriteIDs2){
			this->spriteIDs[i++] = s;
		}
		this->numSprites = (int) spriteIDs2.size();
		lastFrameTime = 0;
		currentSprite = 0;
	}

	~Animation() {}

	void Advance() {
		//add past time to frame time
		lastFrameTime += Time::DeltaTime;
		//is the time for this frame over now?
		if(lastFrameTime >= timeBetweenFrames) {
			lastFrameTime = 0;
			currentSprite++;
			//Check if we have to loop back
			//if this is the end of the animation
			if(currentSprite >= numSprites) {
				if(repeat)
					currentSprite = 0;
				//else, we get stuck on the last frame of the animation
				else
					currentSprite = numSprites - 1;
			}
		}
	}

	int CurrentFrame() { return spriteIDs[currentSprite]; }

	std::string GetString() {
		std::stringstream ret;
		ret << "Anim (" << numSprites << " sprites): ";
		for(int i=0; i < numSprites; i++)
			ret << spriteIDs[i] << " ";
		ret << " time " << timeBetweenFrames
			<< " repeat " << repeat
			<< " current " << currentSprite;
		return ret.str();
	}

private:
	int spriteIDs[MAX_SPRITE_FRAMES];
	int numSprites;
	int currentSprite;
	float timeBetweenFrames;
	bool repeat;
	float lastFrameTime;
};


#endif /* ANIMATION_H_ */
