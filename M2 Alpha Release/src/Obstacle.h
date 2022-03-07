#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__
#include "GLM/glm.hpp"
#include "SDL.h"

class Obstacle {
public:
	Obstacle(SDL_Rect P_S);
	~Obstacle();
	void setPositionSize(SDL_Rect P_S);
	void setIsVisited(bool v);


	SDL_Rect getPosSize();
	bool getIsVisited();

	SDL_Rect positionAndSize;

private:


	bool isVisited = false;
};


#endif /* defined (__OBSTACLE__) */