/*
 * Asset.h
 *
 *  Created on: 26-Dec-2017
 *      Author: pi
 */

#ifndef ASSET_H_
#define ASSET_H_

#include "Vector2.hpp"
#include "Sprite.h"
#include "GameObject.h"
#include "Animation.h"
#include <string.h>
#include <iostream>

/* A asset holds all information which is required to
 * construct a game object. */
class Asset {
public:

	//Construct with single sprite ID
	Asset(int spriteId, const char* name, int layer)
	: spriteId(spriteId), usesAnim(false), layer(layer) {
		strncpy(this->name, name, sizeof(this->name));
	}

	Asset(Animation anim, const char* name, int layer)
	: anim(anim), usesAnim(true), layer(layer) {
		strncpy(this->name, name, sizeof(this->name));
	}

	~Asset() { }

	GameObject* Instantiate(Vector2 position) {
		GameObject* g = new GameObject();
		g->layer = this->layer;
		g->position = position;
		g->SetName(this->name);
		if(!usesAnim) {
			g->spriteID= this->spriteId;
			g->usesAnim = false;
		} else {
			g->usesAnim = true;
			std::cout << "Instantiating with anim. " << std::endl;
			std::cout << anim.GetString() << std::endl;
			g->anim = anim;

			std::cout << "Copied anim: " << std::endl;
			std::cout << g->anim.GetString() << std::endl;
		}
		return g;
	}

private:
	int spriteId;
	Animation anim;
	bool usesAnim;
	char name[20];
	int layer;
};

#endif /* ASSET_H_ */
