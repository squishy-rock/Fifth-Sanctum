#include "StartBackground.h"
#include "TextureManager.h"


StartBackground::StartBackground()
{
	TextureManager::Instance().load("../Assets/textures/bgtitle2.png", "StartBackground");

	const auto size = TextureManager::Instance().getTextureSize("StartBackground");
	//setWidth(size.x);
	//setHeight(size.y);

	setType(START_BACKGROUND);
}

StartBackground::~StartBackground()
= default;

void StartBackground::draw()
{
	// draw the StartBackground
	TextureManager::Instance().draw("StartBackground", 0, 0, 0, 255);
}

void StartBackground::update()
{

}

void StartBackground::clean()
{
}
