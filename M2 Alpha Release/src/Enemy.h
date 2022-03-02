#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "PlayerAnimationState.h"
#include "Sprite.h"
#include "Util.h"
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

	// getters and setters (accessors and mutators)
	float getMaxSpeed() const;
	float getTurnRate() const;
	float getAccelerationRate() const;
	glm::vec2 getDesiredVelocity() const;

	void setMaxSpeed(float speed);
	void setTurnRate(float angle);
	void setAccelerationRate(float rate);
	void setDesiredVelocity(glm::vec2 target_position);

	// public functions
	void Seek();
	void LookWhereYoureGoing(glm::vec2 target_direction);

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;
	PlayerAnimationState lastEnemyDirection;

	// private movement variables
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	// where we want to go
	glm::vec2 m_desiredVelocity;

	// private functions
	void m_move();
};

#endif /* defined (__HUMAN__) */