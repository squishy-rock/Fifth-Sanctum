#pragma once
#ifndef __START_BACKGROUND__
#define __START_BACKGROUND__

#include "DisplayObject.h"

class StartBackground final : public DisplayObject {
public:
	StartBackground();
	~StartBackground();

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