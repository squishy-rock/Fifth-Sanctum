#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	Mix_FreeChunk(m_startButtonSFX);
	Mix_FreeMusic(m_titleTheme);
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		
		TheGame::Instance().quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		Mix_PlayChannel(-1, m_startButtonSFX, 0);
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("WHAT'S UNDER THE BED?", "Dock51", 80, blue, glm::vec2(500.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pStartBackground = new StartBackground();
	addChild(m_pStartBackground, 0, 0);



	m_titleTheme = Mix_LoadMUS("../Assets/audio/DarkTheme.ogg");
	m_startButtonSFX = Mix_LoadWAV("../Assets/audio/Menu1A.wav");
	Mix_PlayMusic(m_titleTheme, -1);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();
}

