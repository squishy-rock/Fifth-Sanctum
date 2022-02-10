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
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pHuman->setAnimationState(PLAYER_RUN_LEFT);
		m_pHuman->getTransform()->position = m_pHuman->getTransform()->position + glm::vec2(-PLAYERSPEED, 0.0f);
		setLastHumanDirection(PLAYER_RUN_LEFT);
		m_pGhost->getTransform()->position.x -= PLAYERSPEED;
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pHuman->setAnimationState(PLAYER_RUN_RIGHT);
		m_pHuman->getTransform()->position = m_pHuman->getTransform()->position + glm::vec2(PLAYERSPEED, 0.0f);
		setLastHumanDirection(PLAYER_RUN_RIGHT);
		m_pGhost->getTransform()->position.x += PLAYERSPEED;
	}

	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pHuman->setAnimationState(PLAYER_RUN_UP);
		m_pHuman->getTransform()->position = m_pHuman->getTransform()->position + glm::vec2(0.0f, -PLAYERSPEED);
		setLastHumanDirection(PLAYER_RUN_UP);
		m_pGhost->getTransform()->position.y -= PLAYERSPEED;
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_pHuman->setAnimationState(PLAYER_RUN_DOWN);
		m_pHuman->getTransform()->position = m_pHuman->getTransform()->position + glm::vec2(0.0f, PLAYERSPEED);
		setLastHumanDirection(PLAYER_RUN_DOWN);
		m_pGhost->getTransform()->position.y += PLAYERSPEED;
	}
	else
	{
		m_pHuman->setAnimationState(getLastHumanDirection());
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
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
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

void PlayScene::setLastHumanDirection(const PlayerAnimationState new_state)
{
	if (new_state == PLAYER_RUN_LEFT)
		New_state = PLAYER_IDLE_LEFT;
	if (new_state == PLAYER_RUN_RIGHT)
		New_state = PLAYER_IDLE_RIGHT;
	if (new_state == PLAYER_RUN_UP)
		New_state = PLAYER_IDLE_UP;
	if (new_state == PLAYER_RUN_DOWN)
		New_state = PLAYER_IDLE_DOWN;

}

PlayerAnimationState PlayScene::getLastHumanDirection()
{
	return New_state;
}
