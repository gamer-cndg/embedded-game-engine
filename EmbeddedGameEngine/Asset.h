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
#include <string.h>

/* A asset holds all information which is required to
 * construct a game object. */
class Asset {
public:
	Asset(int spriteId, const char* name, int layer)
	: spriteId(spriteId), layer(layer) {
		strncpy(this->name, name, sizeof(this->name));
	}
	~Asset() { }

	GameObject* Instantiate(Vector2 position) {
		GameObject* g = new GameObject();
		g->layer = this->layer;
		g->position = position;
		g->SetName(this->name);
		g->spriteID= this->spriteId;
		return g;
	}

private:
	int spriteId;
	char name[20];
	int layer;
};

#endif /* ASSET_H_ */
