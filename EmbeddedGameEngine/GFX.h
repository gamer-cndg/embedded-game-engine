#pragma once

#include "MessageBus.h"
#include "DisplayDriver.h"
#include "SceneManager.h"
#include <array>
#include <algorithm>
#include <vector>
#include <iostream> /* debugging */
#include "Input.h" /* experimental */
#include <chrono> /* for FPS measurement */
using namespace std;
using namespace std::chrono;

enum class GFXCmd {
	LOAD_SPRITE = 1,
	REMOVE_SPRITE = 2
};

class GFX : public MessageBusReceiver<SubsystemType::GFX>
{
public:

	static bool stopGFX;

	static void DrawGameObject(GameObject* g) {
		//Get the sprite
		const void* pixelData = g->sprite->GetPixelData();
		int width = g->sprite->GetWidth();
		int height = g->sprite->GetHeight();
		ColorFormat cFormat = g->sprite->GetColorFormat();
		int x = (int) g->position.X;
		int y = (int) g->position.Y;
		const char* name = (const char*) g->instanceName;
		//std::cout << "drawing " << name << " at " << x << "," << y << std::endl;

		//Test: do scripts processing in GFX thread..
		g->ProcessScripts();

		//Draw its sprite in the buffer.
		displayDriver->DrawBitmap(
				x, y, (uint8_t*)pixelData,
				width, height, cFormat,
				BlendMode::Overwrite);
	}

	static void DrawFrame() {
		//TODO: go over every object
		//and draw its graphical representation
		//on the screen, using the display driver.
		std::vector<GameObject*>* gameObjects
		= SceneManager::GetCurrentGameObjects();

		if(!gameObjects)
			return;

		//We need to draw sprites on lower
		//layers first.
		//std::sort(v2.begin(), v2.end(), GameObject::SortByLayer);
		//TODO: above soting would be better, but it doesn't
		//work. how can this be made more efficient?

		for(int i=0; i < LAYERS_MAX; i++) {
			for(GameObject* g : *gameObjects) {
				if(g->layer == i)
					DrawGameObject(g);
			}
		}
	}

	/*Implements the main render thread thread */
	static THREAD_RET_TYPE GFXThread(void* arg) {
		stopGFX = false;
		int cnt = 0;
		while(!stopGFX) {
		    high_resolution_clock::time_point t1 = high_resolution_clock::now();

			//Update input
			Input::ReadInput();

			displayDriver->ClearFramebuffer();
			DrawFrame();
			displayDriver->DrawFramebuffer();

			//Sleep for some number of milliseconds.
			//OS->Sleep(1);

		    high_resolution_clock::time_point t2 = high_resolution_clock::now();

		    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
		    float fps = 1000 / (duration / 1000.0f);

		    cnt++;
		    if(cnt == 20) {
		    	cout << "DRAWING NEEDED " << duration << " US or " << fps << " FPS" << std::endl;
		    	cnt = 0;
		    }

		}

		std::cout << "Exiting GFX thread now " << std::endl;

		THREAD_RET_STATEMENT;
	}

	void ProcessMessage(MessageBusMsg msg) {
		/* ? */
	}


	GFX();
	~GFX();
};

