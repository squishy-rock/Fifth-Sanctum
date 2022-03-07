#include "Bed.h"

Bed::Bed(SDL_Rect P_S)
{
	setPositionSize(P_S);
}

Bed::~Bed()
{
}

void Bed::setPositionSize(SDL_Rect P_S)
{
	positionAndSize = P_S;
}

void Bed::setIsVisited(bool v)
{
	isVisited = v;
}

SDL_Rect Bed::getPosSize()
{
	return positionAndSize;
}

bool Bed::getIsVisited()
{
	return isVisited;
}
