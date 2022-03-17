#include "Weap.h"
#include "SoundManager.h"
#include "TextureManager.h"

Weap::Weap()
{
	TextureManager::Instance().load("../Assets/textures/bullet.png", "bullet");

	auto size = TextureManager::Instance().getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;

	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
}

Weap::Weap(int x, int y, PlayerAnimationState d) : bulletDir(d)
{
	TextureManager::Instance().load("../Assets/textures/bullet.png", "bullet");

	auto size = TextureManager::Instance().getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(x, y);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;

	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
}

Weap::~Weap()
= default;

void Weap::draw()
{
	TextureManager::Instance().draw("bullet",
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Weap::update()
{
	switch (bulletDir)
	{
	case PLAYER_IDLE_UP:
		getTransform()->position.y -= SPEED;
		break;
	case PLAYER_IDLE_RIGHT:
		getTransform()->position.x += SPEED;
		break;
	case PLAYER_IDLE_DOWN:
		getTransform()->position.y += SPEED;
		break;
	case PLAYER_IDLE_LEFT:
		getTransform()->position.x -= SPEED;
		break;
	default:
		break;
	}
}

void Weap::clean()
{
}
