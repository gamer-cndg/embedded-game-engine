#pragma once

#include "Scene.h"

class SceneManager
{
public:

	static void LoadScene(Scene* s) {
		currScene = s;
		s->InitScene();
	}

	static void AddGameObject(GameObject* g) {
		if(!currScene) return;
		currScene->AddObject(g);
	}

	static GameObject* FindGameObject(const char* name) {
		if(!currScene) return NULL;
		return currScene->FindObject(name);

	}

	static std::vector<GameObject*>* GetCurrentGameObjects() {
		if(currScene == NULL)
			return NULL;
		return currScene->GetAllGameObjects();
	}

	static Scene* GetCurrentScene() {
		return currScene;
	}

	SceneManager();
	~SceneManager();

private:
	static Scene* currScene;
};

