#include "WinScene.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "SDL_Image.h"
#include <algorithm>
#include "SDL_image.h"
#include "bg.h"

WinScene::WinScene()
{
	WinScene::start();
}

WinScene::~WinScene() = default;

void WinScene::draw()
{
	drawDisplayList();
}

void WinScene::update()
{
	updateDisplayList();
}

void WinScene::clean()
{
	removeAllChildren();
}

void WinScene::handleEvents()
{
	EventManager::Instance().update();
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_Q))
	{
		TheGame::Instance().quit();
	}

}

void WinScene::start()
{

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 120,120, 255);
	m_pCongratulationMessage = new Label("Congrats! You Won! :)", "Dock51", 90, { 0,255,0,255 },
		glm::vec2(500.0f, 120.0f));
	m_pCongratulationMessage->setParent(this);
	addChild(m_pCongratulationMessage);

	m_pQuitInstruction = new Label("Press Q to Quit Game", "Consolas", 50, { 0,255,0,255 },
		glm::vec2(500.0f, 400.0f));
	m_pQuitInstruction->setParent(this);
	addChild(m_pQuitInstruction);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();

}
