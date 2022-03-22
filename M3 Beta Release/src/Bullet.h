#pragma once
#ifndef __BULLET__
#define __BULLET__
#include <SDL_rect.h>
#include "DisplayObject.h"

class Bullet : public DisplayObject
{
public:
	Bullet(const SDL_Rect d);
	~Bullet();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};
#endif


