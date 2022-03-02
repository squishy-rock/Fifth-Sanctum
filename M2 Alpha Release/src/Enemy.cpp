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
}

void Enemy::clean()
{
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
