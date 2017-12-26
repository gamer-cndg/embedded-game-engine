#pragma once

/* forward declaration of a gameobject */
class GameObject;

class Behaviour
{
public:

	/* scripts will have to overwrite the Update method */
	virtual void Update() = 0;

	void SetGameObject(GameObject* g) { gameObject = g; }

	Behaviour();
	virtual ~Behaviour();

protected:
	GameObject* gameObject;
};

