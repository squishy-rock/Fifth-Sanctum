#include "Weapon1.h"

#include "SoundManager.h"
#include "TextureManager.h"

Weapon1::Weapon1()
{
	TextureManager::Instance().load("../Assets/textures/bullet.png", "Weap1");

	auto size = TextureManager::Instance().getTextureSize("Weap1");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(WEAPON1);
	getRigidBody()->isColliding = false;

	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
}

//Weapon1::Weapon1(int x, int y, Direction d) /*: bulletDir(d)*/
//{
//	bulletDir = d;
//	TextureManager::Instance().load("../Assets/textures/bullet.png", "Weap1");
//
//	auto size = TextureManager::Instance().getTextureSize("Weap1");
//	setWidth(size.x);
//	setHeight(size.y);
//
//	getTransform()->position = glm::vec2(10,10);
//
//	setType(WEAPON1);
//	getRigidBody()->isColliding = true;
//
//	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
//}

Weapon1::~Weapon1()
= default;

void Weapon1::draw()
{
	TextureManager::Instance().draw("Weap1",
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Weapon1::update()
{
	switch (bulletDir)
	{
	case MUP:
		getTransform()->position.y -= PLAYERSPEED;
		break;
	case MRIGHT:
		getTransform()->position.x += PLAYERSPEED;
		break;
	case MDOWN:
		getTransform()->position.y += PLAYERSPEED;
		break;
	case MLEFT:
		getTransform()->position.x -= PLAYERSPEED;
		break;
	default:
		break;
	}
}

void Weapon1::clean()
{
}

void Weapon1::setBulletDir(Direction d)
{
	bulletDir = d;
}

Direction Weapon1::getBulletDir()
{
	return bulletDir;
}
