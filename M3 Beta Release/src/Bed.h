#pragma once
#ifndef __BED__
#define __BED__
#include "GLM/glm.hpp"
#include "SDL.h"

class Bed {
public:
	Bed(SDL_Rect P_S);
	~Bed();
	void setPositionSize(SDL_Rect P_S);
	void setIsVisited(bool v);


	SDL_Rect getPosSize();
	bool getIsVisited();

	SDL_Rect positionAndSize;

private:
	
	
	bool isVisited = false;
};


#endif /* defined (__BED__) */