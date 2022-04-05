#include "LoseScene.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "SDL_Image.h"
#include <algorithm>
#include "SDL_image.h"
#include "bg.h"

LoseScene::LoseScene()
{
	LoseScene::start();
}

LoseScene::~LoseScene() = default;

void LoseScene::draw()
{
	drawDisplayList();
}

void LoseScene::update()
{
	updateDisplayList();
}

void LoseScene::clean()
{
	removeAllChildren();
}

void LoseScene::handleEvents()
{
	EventManager::Instance().update();

	//Button Event, Set Restart to Main Scene 
	m_pRestartButton->update();
}

void LoseScene::start()
{

	//Soundmanager
	SoundManager::Instance().load("../Assets/audio/Endforgame.mp3", "Endforgame", SOUND_SFX);
	SoundManager::Instance().playSound("Endforgame", 0, -1);


	

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 0, 0, 255);

	SDL_Color red = { 255,0,0,255 };
	m_pLoseInstructions = new Label("Game Over", "Dock51", 80, red, glm::vec2(500.0f, 120.0f));
	m_pLoseInstructions->setParent(this);
	addChild(m_pLoseInstructions);

	//Restart Button
	m_pRestartButton = new Button("../Assets/textures/RestartButton3.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pRestartButton->setActive(false);
			TheGame::Instance().changeSceneState(PLAY_SCENE);
		});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pRestartButton->setAlpha(128);
		});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pRestartButton->setAlpha(255);
		});

	addChild(m_pRestartButton);

	//Quit Button
	m_pQuitButton = new Button("../Assets/textures/QuitButton3.png", "quitButton", QUIT_BUTTON);
	m_pQuitButton->getTransform()->position = glm::vec2(500.0f, 450.0f);
	m_pQuitButton->addEventListener(CLICK, [&]()-> void
		{
			TheGame::Instance().quit();
		});

	m_pQuitButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pQuitButton->setAlpha(128);
		});

	m_pQuitButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pQuitButton->setAlpha(255);
		});

	addChild(m_pQuitButton);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();
}