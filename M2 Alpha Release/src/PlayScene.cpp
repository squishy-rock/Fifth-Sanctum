#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

}

void PlayScene::clean()
{
	Mix_FreeChunk(m_pGunSound);
	Mix_FreeMusic(m_pPlaySceneMusic);
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		if(!CollisionManager::AABBCheck(m_pHuman->leftSenRect,SDL_Rect{ int(m_pNextButton->getTransform()->position.x), int(m_pNextButton->getTransform()->position.y), m_pNextButton->getWidth(), m_pNextButton->getHeight() }))
		//if(!CollisionManager::lineRectCheck(m_pHuman->leftSensorStart, m_pHuman->leftSensorEnd, glm::vec2{ m_pNextButton->getTransform()->position.x, m_pNextButton->getTransform()->position.y }, m_pNextButton->getWidth(), m_pNextButton->getHeight()))
		//if (!CollisionManager::pointRectCheck(m_pHuman->leftSensor, glm::vec2{m_pNextButton->getTransform()->position.x, m_pNextButton->getTransform()->position.y}, m_pNextButton->getWidth(), m_pNextButton->getHeight()))
		{
			//m_pHuman->getTransform()->position = m_pHuman->getTransform()->position + glm::vec2(-PLAYERSPEED, 0.0f);
			//m_pGhost->getTransform()->position.x -= PLAYERSPEED;
			m_pLevel->getTransform()->position.x += PLAYERSPEED;
		}
		m_pHuman->setAnimationState(PLAYER_RUN_LEFT);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_LEFT);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		if (!CollisionManager::AABBCheck(m_pHuman->rightSenRect, SDL_Rect{ int(m_pNextButton->getTransform()->position.x), int(m_pNextButton->getTransform()->position.y), m_pNextButton->getWidth(), m_pNextButton->getHeight() }))
		//if (!CollisionManager::lineRectCheck(m_pHuman->rightSensorStart, m_pHuman->rightSensorEnd, glm::vec2{ m_pNextButton->getTransform()->position.x, m_pNextButton->getTransform()->position.y }, m_pNextButton->getWidth(), m_pNextButton->getHeight()))
		//if (!CollisionManager::pointRectCheck(m_pHuman->rightSensor, glm::vec2{ m_pNextButton->getTransform()->position.x, m_pNextButton->getTransform()->position.y }, m_pNextButton->getWidth(), m_pNextButton->getHeight()))
		{
			//m_pHuman->getTransform()->position = m_pHuman->getTransform()->position + glm::vec2(PLAYERSPEED, 0.0f);
			//m_pGhost->getTransform()->position.x += PLAYERSPEED;
			m_pLevel->getTransform()->position.x -= PLAYERSPEED;
		}
		m_pHuman->setAnimationState(PLAYER_RUN_RIGHT);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_RIGHT);
	}

	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		if (!CollisionManager::AABBCheck(m_pHuman->upSenRect, SDL_Rect{ int(m_pNextButton->getTransform()->position.x), int(m_pNextButton->getTransform()->position.y), m_pNextButton->getWidth(), m_pNextButton->getHeight() }))
		//if (!CollisionManager::lineRectCheck(m_pHuman->upSensorStart, m_pHuman->upSensorEnd, glm::vec2{ m_pNextButton->getTransform()->position.x, m_pNextButton->getTransform()->position.y }, m_pNextButton->getWidth(), m_pNextButton->getHeight()))
		//if (!CollisionManager::pointRectCheck(m_pHuman->upSensor, glm::vec2{ m_pNextButton->getTransform()->position.x, m_pNextButton->getTransform()->position.y }, m_pNextButton->getWidth(), m_pNextButton->getHeight()))
		{
			//m_pHuman->getTransform()->position = m_pHuman->getTransform()->position + glm::vec2(0.0f, -PLAYERSPEED);
			//m_pGhost->getTransform()->position.y -= PLAYERSPEED;
			m_pLevel->getTransform()->position.y += PLAYERSPEED;
		}
		m_pHuman->setAnimationState(PLAYER_RUN_UP);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_UP);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		if (!CollisionManager::AABBCheck(m_pHuman->downSenRect, SDL_Rect{ int(m_pNextButton->getTransform()->position.x), int(m_pNextButton->getTransform()->position.y), m_pNextButton->getWidth(), m_pNextButton->getHeight() }))
		//if (!CollisionManager::lineRectCheck(m_pHuman->downSensorStart, m_pHuman->downSensorEnd, glm::vec2{ m_pNextButton->getTransform()->position.x, m_pNextButton->getTransform()->position.y }, m_pNextButton->getWidth(), m_pNextButton->getHeight()))
		//if (!CollisionManager::pointRectCheck(m_pHuman->downSensor, glm::vec2{ m_pNextButton->getTransform()->position.x, m_pNextButton->getTransform()->position.y }, m_pNextButton->getWidth(), m_pNextButton->getHeight()))
		{
			//m_pHuman->getTransform()->position = m_pHuman->getTransform()->position + glm::vec2(0.0f, PLAYERSPEED);
			//m_pGhost->getTransform()->position.y += PLAYERSPEED;
			m_pLevel->getTransform()->position.y -= PLAYERSPEED;
		}
		m_pHuman->setAnimationState(PLAYER_RUN_DOWN);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_DOWN);
	}
	else
	{
		m_pHuman->setAnimationState(m_pHuman->getLastHumanDirection());
	}

	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}

	// To check Human lives
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_L))
	{
		m_HumanLife->setHumanLife(m_HumanLife->getHumanLife() - 1);
		SDL_Delay(100);
	}

	//Shooting
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		Mix_PlayChannel(-1, m_pGunSound, 0);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Game Level
	m_pLevel = new Level();
	addChild(m_pLevel);

	// Human Sprite
	m_pHuman = new Human();
	addChild(m_pHuman);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, HEIGHT * 0.9f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance().changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, HEIGHT * 0.9f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance().changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);

	// Ghost 
	m_pGhost = new Ghost();
	m_pGhost->getTransform()->position = m_pHuman->getTransform()->position;
	addChild(m_pGhost);

	//Life
	m_HumanLife = new HumanLife();
	addChild(m_HumanLife);

	m_pPlaySceneMusic = Mix_LoadMUS("../Assets/Audio/Night of the Streets.mp3");
	m_pGunSound = Mix_LoadWAV("../Assets/Audio/LaserSFX.mp3");
	Mix_PlayMusic(m_pPlaySceneMusic,-1);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();
}
