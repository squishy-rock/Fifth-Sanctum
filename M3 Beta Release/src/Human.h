#pragma once
#ifndef __HUMAN__
#define __HUMAN__

#include "PlayerAnimationState.h"
#include "Sprite.h"
//#include "Game.h"
#define AnimaSpeed 0.3f

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

	//Setting last direction
	PlayerAnimationState getLastHumanDirection();
	void setLastHumanDirection(const PlayerAnimationState new_state);

	// 4 sides Sensors
	SDL_Rect* upSenRect;
	SDL_Rect* downSenRect;
	SDL_Rect* rightSenRect;
	SDL_Rect* leftSenRect;

	// For collision
	void SetIsColliding(bool b) { isColliding = b; }
	bool GetIsColliding() { return isColliding; }
	int GetTint() { return m_tint; }
	void SetTint(int t) { m_tint = t; }
	void Hit();

	void setAnimationSpeed(float s);


private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
	PlayerAnimationState lastHumanDirection;

	// For collision
	bool isColliding = false;
	int m_tint;
	int hitCount;
	int maxCount;
	float animationSpeed;
};

#endif /* defined (__HUMAN__) */