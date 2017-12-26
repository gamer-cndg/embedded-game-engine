#include <iostream>
#include <SDL.h>
#include "Engine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Input.h"

/* Include platform specific implementations */
//#include "WindowsOSDriver.h"
#include "LinuxOSDriver.h"
#include "SDLDisplayDriver.h"
#include "SDLInputDriver.h"
#include "SDLSoundDriver.h"

//left side
uint32_t myRect[100 * 100 ] = { 0 };
//right side
uint32_t myRect2[800 * 300] = { 0 };

GameObject* player = nullptr;

class MoveBehavior: public Behaviour {
public:
	void Update() {
		Vector2 move = Input::GetGamepad(0)->ReadMovement();
		std::cout << "movement: " << move.X << "," << move.Y << std::endl;
		gameObject->position += move * 3;
	}
};

/* implement our class */
class StartScene : public Scene {
private:
	GameObject g;
public:
	void InitScene() {
		//Construct a test game object and sprite
		Sprite* s = new Sprite((void*)myRect, 100, 100, ColorFormat::R8G8B8A8);
		g.sprite = s;
		g.SetName("Test obj");
		g.position = Vector2(0,0);
		g.layer = 0;
		g.AddScript(new MoveBehavior());
		AddObject(&g);
	}
};

LinuxOSDriver osDriver;
SDLDisplayDriver sdlDisplayDriver;
SDLInputDriver sdlInputDriver;
SDLSoundDriver sdlSoundDriver;

Engine engine(
	(OSDriver*)&osDriver, 
	(DisplayDriver*)&sdlDisplayDriver, 
	(InputDriver*)&sdlInputDriver, 
	(SoundDriver*)&sdlSoundDriver
);

void writeTexture(uint8_t* texture, size_t numBytes, uint8_t r, uint8_t g, uint8_t b) {
	for (size_t i = 0; i < sizeof(myRect); i += 4) {
		texture[i]		= r; //R
		texture[i + 1]	= g; //G
		texture[i + 2]	= b; //B
		texture[i + 3]	= 0; //A
	}
}

int main(int argc, char *argv[]) {

	writeTexture((uint8_t*)myRect, sizeof(myRect), 0xff, 0x00, 0x00);
	writeTexture((uint8_t*)myRect2, sizeof(myRect2), 0xab, 0x00, 0xbc);

	engine.Start();

	StartScene startScene;
	SceneManager::LoadScene(&startScene);
	player = (*(startScene.GetAllGameObjects()->begin()));

	SDL_Event evt;
	bool running = true;
	while(running) {
		SDL_WaitEvent(&evt);

		switch(evt.type) {
		case SDL_QUIT:
			running = false;
			break;
		}

		//SDL_Delay(100);
	}

	std::cout << "Stoping engine now " << std::endl;
	engine.Stop();

	return 0;
}
