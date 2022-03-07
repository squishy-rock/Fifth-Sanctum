#pragma once
#ifndef __bg__
#define __bg__

#include <DisplayObject.h>


class bg final : public DisplayObject {
public:
	bg();
	~bg();

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