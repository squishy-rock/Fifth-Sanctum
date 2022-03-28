#include "PauseScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

PauseScene::PauseScene()
{
	PauseScene::start();
}

PauseScene::~PauseScene()
= default;

void PauseScene::draw()
{
	//Util::DrawFilledRect(glm::vec2{ 0,0 }, WIDTH, HEIGHT, glm::vec4{ 255, 255, 115, 150 }, Renderer::Instance().getRenderer());
	drawDisplayList();
	//Util::DrawFilledRect(glm::vec2( 50, 50 ), WIDTH, HEIGHT, glm::vec4(0.5, 0.5, 0.5, 1 ), Renderer::Instance().getRenderer());
	//Util::DrawRect(glm::vec2(50, 50), WIDTH, HEIGHT, glm::vec4{ 115, 115, 115, 255 }, Renderer::Instance().getRenderer());
}

void PauseScene::update()
{
	updateDisplayList();
	/*if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
		STMA::PopState();
	TheGame::Instance().popS*/
}

void PauseScene::clean()
{
	removeAllChildren();
}

void PauseScene::handleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pRestartButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_R))
	{
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	}
}

void PauseScene::start()
{

	Util::DrawFilledRect(glm::vec2{ 0,0 }, WIDTH, HEIGHT, glm::vec4(115, 115, 115, 255), Renderer::Instance().getRenderer());

	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color gray = { 100, 100, 100, 255 };
	m_label = new Label("PAUSE SCENE", "Dock51", 90, gray, glm::vec2(WIDTH/2, 80.0f));
	m_label->setParent(this);
	addChild(m_label);

	// Resume Button
	m_pResumeButton = new Button("../Assets/textures/resumeButton2.png", "resumeButton", RESUME_BUTTON);
	m_pResumeButton->getTransform()->position = glm::vec2(WIDTH / 2, 340.0f);
	m_pResumeButton->addEventListener(CLICK, [&]()-> void
		{
			m_pResumeButton->setActive(false);
			TheGame::Instance().changeSceneState(PLAY_SCENE);
		});

	m_pResumeButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pResumeButton->setAlpha(128);
		});

	m_pResumeButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pResumeButton->setAlpha(255);
		});
	addChild(m_pResumeButton);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton2.png", "restartButton", RESUME_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2( WIDTH/2, 400.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pRestartButton->setActive(false);
			TheGame::Instance().changeSceneState(START_SCENE);
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

	m_pBackgroundScene = new BackgroundScene();
	addChild(m_pBackgroundScene, 0, 0);

	// Quit Button
	m_pQuitButton = new Button("../Assets/textures/quitButton2.png", "quitButton", QUIT_BUTTON);
	m_pQuitButton->getTransform()->position = glm::vec2(WIDTH / 2, 460.0f);
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


