#include "IndicatorBullet.h"

#include <Windows.h>

#include "TextureManager.h"
#include "Weap.h"


IndicatorBullet::IndicatorBullet()
{
	TextureManager::Instance().load("../Assets/textures/bullets.png", "bullets");
	TextureManager::Instance().load("../Assets/textures/bullets.png", "bullets2");
	TextureManager::Instance().load("../Assets/textures/bullets.png", "bullets3");
	TextureManager::Instance().load("../Assets/textures/bullets.png", "bullets4");
	TextureManager::Instance().load("../Assets/textures/bullets.png", "bullets5");
	TextureManager::Instance().load("../Assets/textures/bullets.png", "bullets6");
	TextureManager::Instance().load("../Assets/textures/bullets.png", "bullets7");
	TextureManager::Instance().load("../Assets/textures/bullets.png", "bullets8");

	const auto size = TextureManager::Instance().getTextureSize("bullets");

	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(32.0f, 65.0f);

	setAmountBullets(8);

	/*setType(LIFE);*/
}

IndicatorBullet::~IndicatorBullet()
= default;

void IndicatorBullet::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (getAmountBullets())
	{
	case 1:
		TextureManager::Instance().draw("bullets", x, y, 0, 255, true);
		break;
	case 2:
		TextureManager::Instance().draw("bullets", x, y, 0, 255, true);
		TextureManager::Instance().draw("bullets2", x*2, y, 0, 255, true);
		break;
	case 3:
		TextureManager::Instance().draw("bullets", x, y, 0, 255, true);
		TextureManager::Instance().draw("bullets2", x*2, y, 0, 255, true);
		TextureManager::Instance().draw("bullets3", x*3, y, 0, 255, true);
		break;
	case 4:
		TextureManager::Instance().draw("bullets", x, y, 0, 255, true);
		TextureManager::Instance().draw("bullets2", x*2, y, 0, 255, true);
		TextureManager::Instance().draw("bullets3", x*3, y, 0, 255, true);
		TextureManager::Instance().draw("bullets4", x*4, y, 0, 255, true);
		break;
	case 5:
		TextureManager::Instance().draw("bullets", x, y, 0, 255, true);
		TextureManager::Instance().draw("bullets2", x * 2, y, 0, 255, true);
		TextureManager::Instance().draw("bullets3", x * 3, y, 0, 255, true);
		TextureManager::Instance().draw("bullets4", x * 4, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 5, y, 0, 255, true);
		break;
	case 6:
		TextureManager::Instance().draw("bullets", x, y, 0, 255, true);
		TextureManager::Instance().draw("bullets2", x * 2, y, 0, 255, true);
		TextureManager::Instance().draw("bullets3", x * 3, y, 0, 255, true);
		TextureManager::Instance().draw("bullets4", x * 4, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 5, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 6, y, 0, 255, true);
		break;
	case 7:
		TextureManager::Instance().draw("bullets", x, y, 0, 255, true);
		TextureManager::Instance().draw("bullets2", x * 2, y, 0, 255, true);
		TextureManager::Instance().draw("bullets3", x * 3, y, 0, 255, true);
		TextureManager::Instance().draw("bullets4", x * 4, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 5, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 6, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 7, y, 0, 255, true);
		break;
	case 8:
		TextureManager::Instance().draw("bullets", x, y, 0, 255, true);
		TextureManager::Instance().draw("bullets2", x * 2, y, 0, 255, true);
		TextureManager::Instance().draw("bullets3", x * 3, y, 0, 255, true);
		TextureManager::Instance().draw("bullets4", x * 4, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 5, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 6, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 7, y, 0, 255, true);
		TextureManager::Instance().draw("bullets5", x * 8, y, 0, 255, true);
		break;
	}

}

void IndicatorBullet::update()
{

}

void IndicatorBullet::clean()
{
}

void IndicatorBullet::m_move()
{
	
}

void IndicatorBullet::m_checkBounds()
{
}

void IndicatorBullet::m_reset()
{
}
