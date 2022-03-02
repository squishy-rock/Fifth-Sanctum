#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"

Enemy::Enemy() : m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Enemy.txt",
		"../Assets/sprites/Enemy.png",
		"spritesheetEnemy");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("spritesheetEnemy"));

	// set frame width
	setWidth(64);

	// set frame height
	setHeight(64);

	getTransform()->position = glm::vec2(WIDTH / 2, HEIGHT / 2);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);

	m_buildAnimations();

	// set sensors positions
	/*upSenRect = new SDL_Rect{ int(getTransform()->position.x) - getWidth() / 2, int(getTransform()->position.y) - getHeight() / 2 - 5, getWidth(), 5 };
	downSenRect = new SDL_Rect{ int(getTransform()->position.x) - getWidth() / 2, int(getTransform()->position.y) + getHeight() / 2, getWidth(), 5 };
	rightSenRect = new SDL_Rect{ int(getTransform()->position.x) + getWidth() / 2, int(getTransform()->position.y) - getHeight() / 2, 5, getHeight() };
	leftSenRect = new SDL_Rect{ int(getTransform()->position.x) - getWidth() / 2 - 5, int(getTransform()->position.y) - getHeight() / 2, 5, getHeight() };*/

	// starting motion properties
	m_maxSpeed = 1.0f; // a maximum number of pixels moved per frame
	m_turnRate = 5.0f; // a maximum number of degrees to turn each time-step
	m_accelerationRate = 2.0f; // a maximum number of pixels to add to the velocity each frame
}

Enemy::~Enemy()
= default;

void Enemy::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Human according to animation state
	switch (m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance().playAnimation("spritesheetEnemy", getAnimation("idleRight"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance().playAnimation("spritesheetEnemy", getAnimation("idleLeft"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_IDLE_UP:
		TextureManager::Instance().playAnimation("spritesheetEnemy", getAnimation("idleUp"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_IDLE_DOWN:
		TextureManager::Instance().playAnimation("spritesheetEnemy", getAnimation("idleDown"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_RUN_DOWN:
		TextureManager::Instance().playAnimation("spritesheetEnemy", getAnimation("runDown"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_RUN_UP:
		TextureManager::Instance().playAnimation("spritesheetEnemy", getAnimation("runUp"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance().playAnimation("spritesheetEnemy", getAnimation("runRight"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance().playAnimation("spritesheetEnemy", getAnimation("runLeft"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	default:
		break;
	}

}

void Enemy::update()
{
	//getTransform()->position.y += 1;
	m_move();
}

void Enemy::clean()
{
}

float Enemy::getMaxSpeed() const
{
	return m_maxSpeed;
}

float Enemy::getTurnRate() const
{
	return m_turnRate;
}

float Enemy::getAccelerationRate() const
{
	return m_accelerationRate;
}

glm::vec2 Enemy::getDesiredVelocity() const
{
	return m_desiredVelocity;
}

void Enemy::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void Enemy::setTurnRate(const float angle)
{
	m_turnRate = angle;
}

void Enemy::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void Enemy::setDesiredVelocity(const glm::vec2 target_position)
{
	m_desiredVelocity = Util::normalize(target_position - getTransform()->position);
}

void Enemy::Seek()
{

	setDesiredVelocity(getTargetPosition());

	const glm::vec2 steering_direction = getDesiredVelocity() - getCurrentDirection();

	LookWhereYoureGoing(steering_direction);

	getRigidBody()->acceleration = getCurrentDirection() * getAccelerationRate();
}

void Enemy::LookWhereYoureGoing(const glm::vec2 target_direction)
{
	float target_rotation = Util::signedAngle(getCurrentDirection(), target_direction) - 90;
	//std::cout << target_rotation;

	const float turn_sensitivity = 3.0f;

	if (getCollisionWhisker()[0])
	{
		target_rotation += getTurnRate() * turn_sensitivity; // turn towards the right

	}
	else if (getCollisionWhisker()[2]) // if right whisker is colliding
	{
		target_rotation -= getTurnRate() * turn_sensitivity; // turn towards the left

	}
	if (getCollisionWhisker()[3])
	{
		target_rotation += getTurnRate() * turn_sensitivity; // turn towards the right

	}
	else if (getCollisionWhisker()[4]) // if right whisker is colliding
	{
		target_rotation -= getTurnRate() * turn_sensitivity; // turn towards the left

	}

	//std::cout << "      " << target_rotation << std::endl;

	// smoothing function that changes the heading of the spaceship slowly to align with the target
	setCurrentHeading(Util::lerpUnclamped(getCurrentHeading(), getCurrentHeading() + target_rotation,
		getTurnRate() * TheGame::Instance().getDeltaTime()));

	// updates the angle of the each of the whiskers 
	updateWhiskers(getWhiskerAngle());
}


void Enemy::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

PlayerAnimationState Enemy::getLastHumanDirection()
{
	return lastEnemyDirection;
}

void Enemy::setLastEnemyDirection(const PlayerAnimationState new_state)
{
	if (new_state == PLAYER_RUN_LEFT)
		lastEnemyDirection = PLAYER_IDLE_LEFT;
	if (new_state == PLAYER_RUN_RIGHT)
		lastEnemyDirection = PLAYER_IDLE_RIGHT;
	if (new_state == PLAYER_RUN_UP)
		lastEnemyDirection = PLAYER_IDLE_UP;
	if (new_state == PLAYER_RUN_DOWN)
		lastEnemyDirection = PLAYER_IDLE_DOWN;
}

void Enemy::m_buildAnimations()
{
	Animation idleDownAnimation = Animation();
	idleDownAnimation.name = "idleDown";
	idleDownAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-idle-down-0"));
	setAnimation(idleDownAnimation);

	Animation idleLeftAnimation = Animation();
	idleLeftAnimation.name = "idleLeft";
	idleLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-idle-left-0"));
	setAnimation(idleLeftAnimation);

	Animation idleUpAnimation = Animation();
	idleUpAnimation.name = "idleUp";
	idleUpAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-idle-up-0"));
	setAnimation(idleUpAnimation);

	Animation idleRightAnimation = Animation();
	idleRightAnimation.name = "idleRight";
	idleRightAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-idle-right-0"));
	setAnimation(idleRightAnimation);

	Animation runDownAnimation = Animation();
	runDownAnimation.name = "runDown";
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-down-0"));
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-down-1"));
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-down-2"));
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-down-3"));
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-down-4"));
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-down-5"));
	setAnimation(runDownAnimation);

	Animation runUpAnimation = Animation();
	runUpAnimation.name = "runUp";
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-up-0"));
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-up-1"));
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-up-2"));
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-up-3"));
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-up-4"));
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-up-5"));
	setAnimation(runUpAnimation);

	Animation runRightAnimation = Animation();
	runRightAnimation.name = "runRight";
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-right-0"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-right-1"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-right-2"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-right-3"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-right-4"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-right-5"));
	setAnimation(runRightAnimation);

	Animation runLeftAnimation = Animation();
	runLeftAnimation.name = "runLeft";
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-left-0"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-left-1"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-left-2"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-left-3"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-left-4"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("enemy-run-left-5"));
	setAnimation(runLeftAnimation);

}

void Enemy::m_move()
{
	Seek();

	//                                   final Position     position term    velocity term     acceleration term
	// kinematic equation for motion --> Pf            =      Pi     +     Vi*(time)    +   (0.5)*Ai*(time * time)

	const float dt = TheGame::Instance().getDeltaTime();

	// compute the position term
	const glm::vec2 initial_position = getTransform()->position;

	// compute the velocity term
	const glm::vec2 velocity_term = getRigidBody()->velocity * dt;

	// compute the acceleration term
	const glm::vec2 acceleration_term = getRigidBody()->acceleration * 0.5f;// *dt;


	// compute the new position
	glm::vec2 final_position = initial_position + velocity_term + acceleration_term;

	getTransform()->position = final_position;

	// add our acceleration to velocity
	getRigidBody()->velocity += getRigidBody()->acceleration;

	// clamp our velocity at max speed
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, getMaxSpeed());
}