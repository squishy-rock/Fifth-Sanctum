#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "PlayerAnimationState.h"
#include "Sprite.h"
//#include "Game.h"
//#define AnimaSpeed 0.3f

class Enemy final : public Sprite
{
public:
	Enemy();
	~Enemy();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);

	//Setting last direction
	PlayerAnimationState getLastHumanDirection();
	void setLastEnemyDirection(const PlayerAnimationState new_state);

	// 4 sides Sensors
	/*SDL_Rect* upSenRect;
	SDL_Rect* downSenRect;
	SDL_Rect* rightSenRect;
	SDL_Rect* leftSenRect;*/

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
	PlayerAnimationState lastEnemyDirection;
};

#endif /* defined (__HUMAN__) */