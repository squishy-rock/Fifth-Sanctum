#include "Human.h"
#include "TextureManager.h"


Human::Human() : m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/Human.txt",
		"../Assets/sprites/Human.png",
		"spritesheet");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(32);

	// set frame height
	setHeight(32);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(HUMAN);

	m_buildAnimations();
}

Human::~Human()
= default;

void Human::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Human according to animation state
	switch (m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance().playAnimation("spritesheet", getAnimation("idleRight"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance().playAnimation("spritesheet", getAnimation("idleLeft"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_IDLE_UP:
		TextureManager::Instance().playAnimation("spritesheet", getAnimation("idleUp"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_IDLE_DOWN:
		TextureManager::Instance().playAnimation("spritesheet", getAnimation("idleDown"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_RUN_DOWN:
		TextureManager::Instance().playAnimation("spritesheet", getAnimation("runDown"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_RUN_UP:
		TextureManager::Instance().playAnimation("spritesheet", getAnimation("runUp"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance().playAnimation("spritesheet", getAnimation("runRight"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance().playAnimation("spritesheet", getAnimation("runLeft"),
			x, y, AnimaSpeed, 0, 255, true);
		break;
	default:
		break;
	}

}

void Human::update()
{
}

void Human::clean()
{
}

void Human::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Human::m_buildAnimations()
{
	Animation idleDownAnimation = Animation();
	idleDownAnimation.name = "idleDown";
	idleDownAnimation.frames.push_back(getSpriteSheet()->getFrame("human-idle-down-0"));
	setAnimation(idleDownAnimation);

	Animation idleLeftAnimation = Animation();
	idleLeftAnimation.name = "idleLeft";
	idleLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("human-idle-left-0"));
	setAnimation(idleLeftAnimation);

	Animation idleUpAnimation = Animation();
	idleUpAnimation.name = "idleUp";
	idleUpAnimation.frames.push_back(getSpriteSheet()->getFrame("human-idle-up-0"));
	setAnimation(idleUpAnimation);

	Animation idleRightAnimation = Animation();
	idleRightAnimation.name = "idleRight";
	idleRightAnimation.frames.push_back(getSpriteSheet()->getFrame("human-idle-right-0"));
	setAnimation(idleRightAnimation);

	Animation runDownAnimation = Animation();
	runDownAnimation.name = "runDown";
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-down-0"));
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-down-1"));
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-down-2"));
	runDownAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-down-3"));
	setAnimation(runDownAnimation);

	Animation runUpAnimation = Animation();
	runUpAnimation.name = "runUp";
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-up-0"));
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-up-1"));
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-up-2"));
	runUpAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-up-3"));
	setAnimation(runUpAnimation);

	Animation runRightAnimation = Animation();
	runRightAnimation.name = "runRight";
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-right-0"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-right-1"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-right-2"));
	runRightAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-right-3"));
	setAnimation(runRightAnimation);

	Animation runLeftAnimation = Animation();
	runLeftAnimation.name = "runLeft";
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-left-0"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-left-1"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-left-2"));
	runLeftAnimation.frames.push_back(getSpriteSheet()->getFrame("human-run-left-3"));
	setAnimation(runLeftAnimation);

}
