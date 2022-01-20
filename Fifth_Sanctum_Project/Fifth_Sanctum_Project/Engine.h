#pragma once
#ifndef _ENGINE_H_ // Portable. Oldschool. Better standard.
#define _ENGINE_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h> 
#include "Missile.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include <vector> 
#define FPS 60
#define WIDTH 1000
#define HEIGHT 650
#define SPEED 3

using namespace std;


class Engine
{
private:
	
public:

	

	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void HandleEvents();
	bool KeyDown(SDL_Scancode c);
	void Update();
	void Render();
	void Clean();
	void Wake();
	void Sleep();
	int Run();
};
#endif