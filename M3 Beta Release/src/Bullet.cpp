#include "Bullet.h"

#include <SDL_image.h>
#include <Windows.h>

#include "Renderer.h"
#include "SoundManager.h"
#include "TextureManager.h"


Bullet::Bullet(const SDL_Rect d)
{
	TextureManager::Instance().load("../Assets/textures/bullets.png", "Bullet");

	const auto size = TextureManager::Instance().getTextureSize("Bullet");

	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position.x = d.x;
	getTransform()->position.y = d.y;

	setType(ITEM);
}

Bullet::~Bullet()
= default;


void Bullet::draw()
{
	//alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;



	TextureManager::Instance().draw("Bullet", x, y, 0, 255, false);
}

void Bullet::update()
{

}

void Bullet::clean()
{
}



void Bullet::m_move()
{

}

void Bullet::m_checkBounds()
{
}

void Bullet::m_reset()
{
}
