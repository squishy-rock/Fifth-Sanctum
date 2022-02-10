#pragma once
#ifndef __HUMAN__
#define __HUMAN__

#include "PlayerAnimationState.h"
#include "Sprite.h"
#define AnimaSpeed 0.2f

class Human final : public Sprite
{
public:
	Human();
	~Human();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__HUMAN__) */