#pragma once
#ifndef __LEVEL__
#define __LEVEL__

#include "DisplayObject.h"

class Level final : public DisplayObject {
public:
	Level();
	~Level();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};


#endif /* defined (__TARGET__) */