/*
 * SpriteManager.h
 *
 *  Created on: 26-Dec-2017
 *      Author: pi
 */

#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include "Sprite.h"
#include <map>

#define MAX_SPRITES 20

/* GameObjects should reference sprites by their ID.
 * This way, memory management is much easier.
 * Every sprite ID is unique to the sprite loaded.
 * Multiple GameObjects can point to the same sprite
 * id at once. */

/* the sprite manager manages sprite in a static array. */
class SpriteManager {
public:

	/* Register a sprite */
	static void Init();
	static int RegisterSprite(Sprite* s);
	static Sprite* GetSprite(int id);
	static void DestroySprite(int id);
	static void DestroyAllSprites();

	SpriteManager();
	virtual ~SpriteManager();

private:
	static std::map<int, Sprite*> sprites;
	static int spriteNum;
};

#endif /* SPRITEMANAGER_H_ */
