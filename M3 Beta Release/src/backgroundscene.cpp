#include "backgroundscene.h"
#include "TextureManager.h"


BackgroundScene::BackgroundScene()
{
	TextureManager::Instance().load("../Assets/textures/background.jpg", "BackgroundScene");

	const auto size = TextureManager::Instance().getTextureSize("BackgroundScene");
	//setWidth(size.x);
	//setHeight(size.y);

	setType(START_BACKGROUND);
}

BackgroundScene::~BackgroundScene()
= default;

void BackgroundScene::draw()
{
	// draw the BackgroundScene
	TextureManager::Instance().draw("BackgroundScene", 0, 0, 0, 255);
}

void BackgroundScene::update()
{

}

void BackgroundScene::clean()
{
}
