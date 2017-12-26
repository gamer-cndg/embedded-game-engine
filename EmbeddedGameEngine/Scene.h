#pragma once

#include "GameObject.h"
#include "SpriteManager.h"
#include <vector>

/* Scenes are user-provided classes.. */
class Scene
{
public:

	virtual void InitScene() = 0;

	void AddObject(GameObject* g) {
		gameObjects.push_back(g);
	}

	GameObject* FindObject(const char* name) {
		return nullptr;
	}

	std::vector<GameObject*>* GetAllGameObjects() {
		return &gameObjects;
	}

	void UnloadScene() {
		//Delete every game object
		for(GameObject* g : gameObjects) {
			//Destruct gameobject (clear all scripts)
			g->Destruct();
			//Unload the sprite for that
			SpriteManager::DestroySprite(g->spriteID);
			delete g;
		}
		gameObjects.clear();
		gameObjects.shrink_to_fit();
	}

	Scene();
	~Scene();

private:
	std::vector<GameObject*> gameObjects;
};

