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

	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_W))
		if (CheckKeyList('W'))DeleteKeyList('W');
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		if (!CheckKeyList('W'))keyList.push_back('W');
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_S))
		if (CheckKeyList('S'))DeleteKeyList('S');
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		if (!CheckKeyList('S'))keyList.push_back('S');
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_A))
		if (CheckKeyList('A'))DeleteKeyList('A');
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		if (!CheckKeyList('A'))keyList.push_back('A');
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_D))
		if (CheckKeyList('D'))DeleteKeyList('D');
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		if (!CheckKeyList('D'))keyList.push_back('D');

	/* Debug
	if (keyList.size() > 0)
		std::cout << keyList.size() << (char)keyList[keyList.size() - 1] << std::endl;
	else
		std::cout << keyList.size() << std::endl;
	*/

	char key = keyList.size() > 0 ? ((char)keyList[keyList.size() - 1]) : 0;

	if (key == 'W')
	{
		m_pHuman->setAnimationState(PLAYER_RUN_UP);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_UP);
	}
	else if (key == 'A')
	{
		m_pHuman->setAnimationState(PLAYER_RUN_LEFT);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_LEFT);
		int humanX = m_pHuman->getTransform()->position.x;
		if (humanX - PLAYERSPEED >= m_pHuman->getWidth() /2.0f) //to make sure sprite doesnt go off screen, but 0,0 is middle of sprite so this clamps it to half sprite's width
		{
			m_pHuman->getTransform()->position.x -= PLAYERSPEED;
		}
	}
	else if (key == 'S')
	{
		m_pHuman->setAnimationState(PLAYER_RUN_DOWN);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_DOWN);
	}
	else if (key == 'D')
	{
		m_pHuman->setAnimationState(PLAYER_RUN_RIGHT);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_RIGHT);
		m_pHuman->getTransform()->position.x += PLAYERSPEED;
	}
	else
	{
		m_pHuman->setAnimationState(m_pHuman->getLastHumanDirection());
	}
}


void StartScene::start()
{
	const SDL_Color red = { 255, 0, 0, 255 };
	m_pStartLabel = new Label("WHAT'S UNDER THE BED?", "Dock51", 80, red, glm::vec2(500.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel, 0, 1);

	const SDL_Color white = { 255, 255, 255, 255 };
	m_pInstructionsLabel = new Label("Use A D keys to move to the door to start", "Consolas", 18, white, glm::vec2(500.0f, 660.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel, 0, 1);

	m_pStartBackground = new StartBackground();
	addChild(m_pStartBackground, 0, 0);

	m_pHuman = new Human();
	m_pHuman->setAnimationSpeed(0.3);
	m_pHuman->getTransform()->position = glm::vec2{40, 588};
	addChild(m_pHuman, 1, 1);


	m_titleTheme = Mix_LoadMUS("../Assets/audio/DarkTheme.ogg");
	m_startButtonSFX = Mix_LoadWAV("../Assets/audio/Menu1A.wav");
	Mix_PlayMusic(m_titleTheme, -1);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();
}

