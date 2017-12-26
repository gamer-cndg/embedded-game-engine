/*
 * SpriteManager.cpp
 *
 *  Created on: 26-Dec-2017
 *      Author: pi
 */

#include "SpriteManager.h"

std::map<int, Sprite*> SpriteManager::sprites;
int SpriteManager::spriteNum =0;

void SpriteManager::Init() {
}

int SpriteManager::RegisterSprite(Sprite* s) {
	int newNum = ++spriteNum;
	sprites[newNum] = s;
	return newNum;
}

Sprite* SpriteManager::GetSprite(int id) {
	//does this ID exist?
	if(sprites.count(id) != 0)
		return sprites[id];
	else
		return nullptr;
}

void SpriteManager::DestroySprite(int id) {
	std::map<int, Sprite*>::iterator it = sprites.find(id);
	if(it != sprites.end()) {
		Sprite* s = it->second;
		//Remove from map
		sprites.erase(it);
		//More to do than just free the object?
		delete s;
	}
}

void SpriteManager::DestroyAllSprites() {
	for(std::pair<int, Sprite*> entry : sprites) {
		delete entry.second;
	}
	sprites.clear();
}

/* there are only static functions. */
SpriteManager::SpriteManager() { }
SpriteManager::~SpriteManager() { }
