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
	Util::DrawRect(glm::vec2{ tileLocation[1]->x, tileLocation[1]->y }, 32, 32);

	//////////// this is to draw rect for all collider object
	//for (int i = 0; i < localLocation.size(); i++)
	//{
		//Util::DrawRect(glm::vec2{ tileLocation[i]->x, tileLocation[i]->y }, tileLocation[i]->w, tileLocation[i]->h);
	//}
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
	for (unsigned i = 0; i < tileLocation.size(); i++)
	{
		delete tileLocation[i]; 
		tileLocation[i] = nullptr; 
	}
	tileLocation.clear(); 
	tileLocation.shrink_to_fit(); 
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		if (!checkLeftSensor())
		{
			m_pLevel->getTransform()->position.x += PLAYERSPEED;
			for (int i = 0; i < tileLocation.size(); i++)
			{
				tileLocation[i]->x += PLAYERSPEED;
			}
		}
		m_pHuman->setAnimationState(PLAYER_RUN_LEFT);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_LEFT);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		if (!checkRightSensor())
		{
			m_pLevel->getTransform()->position.x -= PLAYERSPEED;
			for (int i = 0; i < tileLocation.size(); i++)
			{
				tileLocation[i]->x -= PLAYERSPEED;
			}

		}
		m_pHuman->setAnimationState(PLAYER_RUN_RIGHT);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_RIGHT);
	}

	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		if(!checkUpSensor())
		{
			m_pLevel->getTransform()->position.y += PLAYERSPEED;
			for (int i = 0; i < tileLocation.size(); i++)
			{
				tileLocation[i]->y += PLAYERSPEED;
			}
		}
		m_pHuman->setAnimationState(PLAYER_RUN_UP);
		m_pHuman->setLastHumanDirection(PLAYER_RUN_UP);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		if (!checkDownSensor())
		{
			m_pLevel->getTransform()->position.y -= PLAYERSPEED;
			for (int i = 0; i < tileLocation.size(); i++)
			{
				tileLocation[i]->y -= PLAYERSPEED;
			}
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

	initTileLocation();

	// Human Sprite
	m_pHuman = new Human();
	addChild(m_pHuman);

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

bool PlayScene::checkUpSensor()
{
	for (SDL_Rect* r : tileLocation)
	{
		if (CollisionManager::AABBCheck(m_pHuman->upSenRect, r))
		{
			return true;
		}
	}
	return false;
}

bool PlayScene::checkDownSensor()
{
	for (SDL_Rect* r : tileLocation)
	{
		if (CollisionManager::AABBCheck(m_pHuman->downSenRect, r))
		{
			return true;
		}
	}
	return false;
}

bool PlayScene::checkRightSensor()
{
	for (SDL_Rect* r : tileLocation)
	{
		if (CollisionManager::AABBCheck(m_pHuman->rightSenRect, r))
		{
			return true;
		}
	}
	return false;
}

bool PlayScene::checkLeftSensor()
{
	for (SDL_Rect* r : tileLocation)
	{
		if (CollisionManager::AABBCheck(m_pHuman->leftSenRect, r))
		{
			return true;
		}
	}
	return false;
}

void PlayScene::initTileLocation()
{
	int xLocation = m_pLevel->getTransform()->position.x - m_pLevel->getWidth() / 2;
	int yLocation = m_pLevel->getTransform()->position.y - m_pLevel->getHeight() / 2;
	int xLocOnMap[] = {10, 11, 12, 13, 14, 15}; // we need to add all the location of the walls on the map
	int yLocOnMap[] = {78, 78, 78, 78, 78, 78 }; // we need to add all the location of the walls on the map
	
	tileLocation.push_back(new SDL_Rect{ 10 * 32 - xLocation, 11 * 32 + yLocation, 32 * 80, 32 });  // up side wall
	tileLocation.push_back(new SDL_Rect{ 10 * 32 - xLocation, 90 * 32 + yLocation,32 * 80, 32 });  // down side wall
	tileLocation.push_back(new SDL_Rect{ 90 * 32 - xLocation, 12 * 32 + yLocation, 32,32 * 80 });  // right side wall
	tileLocation.push_back(new SDL_Rect{ 9 * 32 - xLocation, 12 * 32 + yLocation, 32,32 * 80 });  // left side wall

	// First horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 31 && i != 32 && i != 33 && i != 34 && i != 52 && i != 53 && i != 54 && i != 55 && i != 83 && i != 84 && i != 85 && i != 86)
		{
			localLocation.push_back(SDL_Point{ i, 78 });
			localLocation.push_back(SDL_Point{ i, 76 });
		}
	}

	// Secont horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 14 && i != 15 && i != 16 && i != 17 && i != 57 && i != 58 && i != 59 && i != 60 && i != 81 && i != 82 && i != 83 && i != 84)
		{
			localLocation.push_back(SDL_Point{ i, 65 });
			localLocation.push_back(SDL_Point{ i, 63 });
		}
	}

	// Third horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 49 && i != 50 && i != 51 && i != 52 && i != 66 && i != 67 && i != 68 && i != 69)
		{
			localLocation.push_back(SDL_Point{ i, 56 });
			localLocation.push_back(SDL_Point{ i, 58 });
		}
	}

	// Forth horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 11 && i != 12 && i != 13 && i != 14 && i != 23 && i != 24 && i != 25 && i != 26 && i != 36 && i != 37 && i != 38 && i != 39 && i != 82 && i != 83 && i != 84 && i != 85)
		{
			localLocation.push_back(SDL_Point{ i, 42 });
			localLocation.push_back(SDL_Point{ i, 44 });
		}
	}

	// Fifth horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 23 && i != 24 && i != 25 && i != 26 && i != 57 && i != 58 && i != 59 && i != 60 && i != 78 && i != 79 && i != 80 && i != 81)
		{
			localLocation.push_back(SDL_Point{ i, 30 });
			localLocation.push_back(SDL_Point{ i, 32 });
		}
	}

	// Sixth horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 30 && i != 31 && i != 32 && i != 33 && i != 49 && i != 50 && i != 51 && i != 52 && i != 82 && i != 83 && i != 84 && i != 85)
		{
			localLocation.push_back(SDL_Point{ i, 23 });
			localLocation.push_back(SDL_Point{ i, 25 });
		}
	}

	SDL_Point H_L[] = { {30, 77}, {35, 77}, {51, 77}, {56, 77}, {82, 77}, {87, 77}, {13, 64}, {18, 64}, {56, 64}, 
						{61, 64}, {80, 64}, {85, 64}, {48, 57}, {53, 57}, {65, 57}, {70, 57}, {10, 43}, {15, 43}, 
						{22, 43}, {27, 43}, {35, 43}, {40, 43}, {81, 43}, {86, 43}, {22, 31}, {27, 31}, {56, 31}, 
						{61, 31}, {77, 31}, {82, 31}, {29, 24}, {34, 24}, {48, 24}, {53, 24}, {81, 24}, {86, 24} };

	for (int i = 0; i < sizeof(H_L); i++)
	{
		localLocation.push_back(H_L[i]);
	}

	for (int i = 0; i < localLocation.size(); i++)
	{
		tileLocation.push_back(new SDL_Rect{ localLocation[i].x * 32 - xLocation, localLocation[i].y * 32 + yLocation, 32,32 });
	}

	/*for (int i = 0; i < sizeof(xLocOnMap); i++)
	{
		tileLocation.push_back(new SDL_Rect{ xLocOnMap[i] * 32 - xLocation, yLocOnMap[i] * 32 + yLocation, 32,32});
	}*/

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
