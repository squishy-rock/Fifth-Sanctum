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
	glm::vec2 upSensor;
	glm::vec2 downSensor;
	glm::vec2 rightSensor;
	glm::vec2 leftSensor;

	SDL_Rect* upSenRect;
	SDL_Rect* downSenRect;
	SDL_Rect* rightSenRect;
	SDL_Rect* leftSenRect;

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
	PlayerAnimationState lastHumanDirection;
};

#endif /* defined (__HUMAN__) */