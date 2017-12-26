#pragma once

#include "GameObject.h"
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

	Scene();
	~Scene();

private:
	std::vector<GameObject*> gameObjects;
};

