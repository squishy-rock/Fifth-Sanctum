#include "Diamond.h"

#include <SDL_image.h>
#include <Windows.h>

#include "Renderer.h"
#include "SoundManager.h"
#include "TextureManager.h"


Diamond::Diamond(const SDL_Rect d)
{
	TextureManager::Instance().load("../Assets/textures/diamond.png", "diamond");

	const auto size = TextureManager::Instance().getTextureSize("diamond");

	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position.x = d.x;
	getTransform()->position.y = d.y;

	setType(ITEM);
}

Diamond::~Diamond()
= default;


void Diamond::draw()
{
	//alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;



	TextureManager::Instance().draw("diamond", x, y, 0, 255, false);
}

void Diamond::update()
{

}

void Diamond::clean()
{
}



void Diamond::m_move()
{

}

void Diamond::m_checkBounds()
{
}

void Diamond::m_reset()
{
}
