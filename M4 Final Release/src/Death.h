#pragma once
#ifndef __DEATH__
#define __DEATH__

#include "Sprite.h"
#define AnimaSpeed 0.3f

class Death final : public Sprite
{
public:
	Death();
	~Death();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	bool getIsDone() { return isDone; }

private:
	void m_buildAnimations();
	bool isDone;
	int numAnim;
};

#endif /* defined (__HUMAN__) */