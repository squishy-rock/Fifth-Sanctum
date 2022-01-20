#include <iostream>
#include "Engine.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Missile.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include <vector> 

Engine e;

int main(int argc, char* argv[])
{
	return e.Run();
}

