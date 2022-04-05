#pragma once
#ifndef __DIAMOND__
#define __DIAMOND__
#include <SDL_rect.h>
#include <SDL_render.h>

#include "DisplayObject.h"
class Diamond : public DisplayObject
{
public:
	Diamond(const SDL_Rect d);
	~Diamond();

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