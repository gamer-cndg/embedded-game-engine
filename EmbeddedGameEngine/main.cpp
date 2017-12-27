#include <iostream>
#include <vector>
#include <SDL.h>
#include "Engine.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Input.h"
#include "Asset.h"
#include "Camera.h"

/* Include platform specific implementations */
//#include "WindowsOSDriver.h"
#include "LinuxOSDriver.h"
#include "SDLDisplayDriver.h"
#include "SDLInputDriver.h"
#include "SDLSoundDriver.h"

//left side
uint32_t myRect[20 * 20] = { 0 };
//right side
uint32_t myRect2[800 * 300] = { 0 };

std::vector<int> LoadAnims(const char* basepath, int numAnims) {
	char baseBuf[100];
	std::vector<int> spriteIDs;
	for(int i=0; i < numAnims; i++) {
		snprintf(baseBuf, sizeof(baseBuf), "%s (%d).png", basepath, (i+1));
		int id = (SpriteManager::RegisterSprite(Sprite::FromPNG(baseBuf)));
		std::cout << "Loaded sprite id " << id << std::endl;
		spriteIDs.push_back(id);
	}
	return spriteIDs;
}


class MoveBehavior: public Behaviour {
public:
	void Update() {
		Vector2 move = Input::GetGamepad(0)->ReadMovement();
		//std::cout << "movement: " << move.X << "," << move.Y << std::endl;

		if(Input::GetGamepad(0)->IsButtonDown(GamePadButton::A))
			gameObject->position += move * Time::DeltaTime * 100;
		else
			Camera::position += move * Time::DeltaTime * 100;

		//Move object, make camera look at game object
		//gameObject->position += move * Time::DeltaTime * 100;
		//Camera::position = gameObject->position;
	}
};

/* implement our class */
class StartScene : public Scene {
public:
	void InitScene() {
		//Register all Sprites
		//Sprite* redRect = new Sprite((void*)myRect, 20, 20, ColorFormat::R8G8B8A8);
		Sprite* redRect = Sprite::FromPNG("/home/pi/Downloads/png/Idle (1).png");
		int redRectId = SpriteManager::RegisterSprite(redRect);

		//Construct a test game object and sprite
		Asset a(redRectId, "testobj", 0);
		GameObject* g = a.Instantiate(Vector2(0,0));
		g->AddScript(new MoveBehavior());
		AddObject(g);

		//Add another copy to the scene
		/*GameObject* g2 = a.Instantiate(Vector2(50,50));
		g2->layer = 1; //Draw this object *over* the player
		AddObject(g2);*/

		//Create an asset with the animated santa claus
		std::vector<int> anims = LoadAnims("/home/pi/Downloads/png/Idle", 12);
		std::cout << "Printing returned ids " ;
		for(int id : anims) {
			std::cout << id << " ";
		}
		std::cout << endl;
		Animation idleAnim(anims, 50 / 1000.0f, true);
		std::cout << "Loaded anim " << idleAnim.GetString() << std::endl;

		Asset santaClaus(idleAnim, "santa", 1);
		AddObject(santaClaus.Instantiate(Vector2(50,50)));
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

	//Seed RNG
	srand(time(NULL));

	writeTexture((uint8_t*)myRect, sizeof(myRect), 0xff, 0x00, 0x00);
	writeTexture((uint8_t*)myRect + sizeof(myRect)/2 , sizeof(myRect)/2, 0x00, 0xff, 0x00);

	writeTexture((uint8_t*)myRect2, sizeof(myRect2), 0xab, 0x00, 0xbc);

	engine.Start();

	StartScene startScene;
	SceneManager::LoadScene(&startScene);

	SDL_Event evt;
	bool running = true;
	while(running) {
		SDL_WaitEvent(&evt);
		switch(evt.type) {
		case SDL_QUIT:
			running = false;
			break;
		}
	}

	std::cout << "Stoping engine now " << std::endl;
	engine.Stop();

	return 0;
}
