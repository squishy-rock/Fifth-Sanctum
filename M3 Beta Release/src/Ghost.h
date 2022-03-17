#pragma once
#ifndef __GHOST__
#define __GHOST__

#include "DisplayObject.h"

class Ghost final : public DisplayObject {
public:
	Ghost();
	~Ghost();

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