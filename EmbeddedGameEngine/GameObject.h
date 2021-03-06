#pragma once

#include "Vector2.hpp"
#include "Sprite.h"
#include "Behaviour.h"
#include "Animation.h"
#include <vector>
#include <string.h>
#include <iostream>

class GameObject
{
public:
	Vector2 position;
	int spriteID;
	char instanceName[10];
	int layer;
	Animation anim;
	bool usesAnim;

	int GetSpriteID() {
		if(usesAnim) {
			//std::cout << "Using anim " << anim.GetString() << std::endl;
			return anim.CurrentFrame();
		}
		else
			return spriteID;
	}

	void ProcessAnimation() {
		if(usesAnim)
			anim.Advance();
	}

	void AddScript(Behaviour* b) {
		b->SetGameObject(this);
		scripts.push_back(b);
	}

	/* execute the Update function in all
	 * scripts attached to this object */
	void ProcessScripts() {
		for(Behaviour* s : scripts) {
			s->Update();
		}
	}

	void SetName(const char* instName) {
		strncpy(instanceName, instName, sizeof(instanceName));
	}

	static bool SortByLayer(const GameObject& g1, const GameObject& g2) {
		return g1.layer < g2.layer;
	}

	/* Remove every script */
	void Destruct() {
		for(Behaviour* b : scripts) {
			delete b;
		}
	}

	GameObject() { }
	~GameObject();

private:
	std::vector<Behaviour*> scripts;
};
