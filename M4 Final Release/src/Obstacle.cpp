#include "Obstacle.h"

Obstacle::Obstacle(SDL_Rect P_S)
{
	setPositionSize(P_S);
}

Obstacle::~Obstacle()
{
}

void Obstacle::setPositionSize(SDL_Rect P_S)
{
	positionAndSize = P_S;
}

void Obstacle::setIsVisited(bool v)
{
	isVisited = v;
}

SDL_Rect Obstacle::getPosSize()
{
	return positionAndSize;
}

bool Obstacle::getIsVisited()
{
	return isVisited;
}
