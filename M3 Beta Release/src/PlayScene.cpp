#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI

#include <Windows.h>

#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include <iostream>

using namespace std;


PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	//Util::DrawRect(glm::vec2{ m_pBed[0]->getPosSize().x, m_pBed[0]->getPosSize().y}, m_pBed[0]->getPosSize().w, m_pBed[0]->getPosSize().h);

	/*for (int i = 0; i < m_pDiamond.size(); i++)
	{
		m_pDiamond[i]->draw();
	}*/
	/*TextureManager::Instance().draw("box", tileLocation[0]->x, tileLocation[0]->y, 0, 255, false);
	TextureManager::Instance().draw("box", tileLocation[1]->x, tileLocation[1]->y, 0, 255, false);*/

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
	/*Util::DrawRect(glm::vec2{ tileLocation[1]->x, tileLocation[1]->y }, 32, 32);*/
	if (m_getGridColliderEnabled())
	{
		//////////// this is to draw rect for obstacle object
		for (Obstacle* o : m_pObstacle)
		{
			Util::DrawRect(glm::vec2{ o->getPosSize().x, o->getPosSize().y }, o->getPosSize().w, o->getPosSize().h);
		}

		//////////// this is to draw rect for bed object
		for (Bed* bed : m_pBed)
		{
			Util::DrawRect(glm::vec2{ bed->getPosSize().x, bed->getPosSize().y }, bed->getPosSize().w, bed->getPosSize().h);
		}

		//////////// this is to draw rect for all collider object
		for (int i = 0; i < localLocation.size(); i++)
		{
			Util::DrawRect(glm::vec2{ tileLocation[i]->x, tileLocation[i]->y }, tileLocation[i]->w, tileLocation[i]->h);
		}
		
		/////////// this is to draw the player sensors 
		Util::DrawRect(glm::vec2{ m_pHuman->upSenRect->x, m_pHuman->upSenRect->y }, m_pHuman->upSenRect->w, m_pHuman->upSenRect->h);
		Util::DrawRect(glm::vec2{ m_pHuman->downSenRect->x, m_pHuman->downSenRect->y }, m_pHuman->downSenRect->w, m_pHuman->downSenRect->h);
		Util::DrawRect(glm::vec2{ m_pHuman->rightSenRect->x, m_pHuman->rightSenRect->y }, m_pHuman->rightSenRect->w, m_pHuman->rightSenRect->h);
		Util::DrawRect(glm::vec2{ m_pHuman->leftSenRect->x, m_pHuman->leftSenRect->y }, m_pHuman->leftSenRect->w, m_pHuman->leftSenRect->h);

		//////////// this is to draw rect for all bed collider
		/*for (SDL_Rect* bed: bedLocation)
		{
			Util::DrawRect(glm::vec2{ bed->x, bed->y }, bed->w, bed->h);
		}*/

		//for (Enemy* e : m_pEnemy)
		//{
		//	for (SDL_Rect* box : tileLocation)
		//	{
		//		// Draw Whiskers
		//		Util::DrawLine(e->getTransform()->position, e->getLeftLOSEndPoint(), e->getLineColour(0));
		//		Util::DrawLine(e->getTransform()->position, e->getMiddleLOSEndPoint(), e->getLineColour(1));
		//		Util::DrawLine(e->getTransform()->position, e->getRightLOSEndPoint(), e->getLineColour(2));
		//		Util::DrawLine(e->getTransform()->position, e->getLeft2LOSEndPoint(), e->getLineColour(3));
		//		Util::DrawLine(e->getTransform()->position, e->getRight2LOSEndPoint(), e->getLineColour(4));

		//		// obstacle dimention information / aliases
		//		const auto boxWidth = box->w;
		//		const int halfBoxWidth = boxWidth;// *0.5f;
		//		const auto boxHeight = box->h;
		//		const int halfBoxHeight = boxHeight;// *0.5f;
		//		const auto boxStart = glm::vec2{ box->x, box->y };// -glm::vec2(halfBoxWidth, halfBoxHeight);

		//		// check every whisker to see if it is colliding with the obstacle
		//		e->getCollisionWhisker()[0] = CollisionManager::lineRectCheck(e->getTransform()->position, e->getLeftLOSEndPoint(), glm::vec2{box->x, box->y}, box->w, box->h);
		//		e->getCollisionWhisker()[1] = CollisionManager::lineRectCheck(e->getTransform()->position, e->getMiddleLOSEndPoint(), boxStart, boxWidth, boxHeight);
		//		e->getCollisionWhisker()[2] = CollisionManager::lineRectCheck(e->getTransform()->position, e->getRightLOSEndPoint(), boxStart, boxWidth, boxHeight);
		//		e->getCollisionWhisker()[3] = CollisionManager::lineRectCheck(e->getTransform()->position, e->getLeft2LOSEndPoint(), boxStart, boxWidth, boxHeight);
		//		e->getCollisionWhisker()[4] = CollisionManager::lineRectCheck(e->getTransform()->position, e->getRight2LOSEndPoint(), boxStart, boxWidth, boxHeight);
		//		//std::cout << e->getCollisionWhisker()[0] << std::endl;
		//		for (int i = 0; i < 5; ++i)
		//		{
		//			e->setLineColour(i, (e->getCollisionWhisker()[i]) ? glm::vec4(1, 0, 0, 1) : glm::vec4(0, 1, 0, 1));
		//		}
		//	}
		//}
	}

	// For Enemy indicator
	if (m_pEnemy.size() > 0)
	{
		SDL_Rect dst = { 770,5,64,64 }, src = { 256,64,64,64 };
		SDL_RenderCopy(Renderer::Instance().getRenderer(), m_pCountEnemyT, &src, &dst);
	}

	/*SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 100, 0, 255);
	SDL_RenderFillRectF(Renderer::Instance().getRenderer(), NULL);*/
}

void PlayScene::update()
{
	

	for (int i = 0 ; i < m_pDeath.size(); i++)
	{
		if (m_pDeath[i]->getIsDone() == true)
		{
			removeChild(m_pDeath[i]);
			m_pDeath[i] = nullptr;
			m_pDeath.erase(m_pDeath.begin() + i);
			m_pDeath.shrink_to_fit();
		}
	}

	// Bullet VS Walls collision
	if (m_pPlayerFire.size() > 0)
	{
		for (unsigned i = 0; i < m_pPlayerFire.size(); i++)
		{
			SDL_Rect temp = { int(m_pPlayerFire[i]->getTransform()->position.x), int(m_pPlayerFire[i]->getTransform()->position.y),
									m_pPlayerFire[i]->getWidth(), m_pPlayerFire[i]->getHeight() };
			for (SDL_Rect* r : tileLocation)
			{
				if (CollisionManager::AABBCheck(&temp, r))
				{
					// TODO: add sound effect for bullet wall collision

					removeChild(m_pPlayerFire[i]);
					//delete m_pPlayerFire[i];  // this line causing error
					m_pPlayerFire[i] = nullptr;
					m_pPlayerFire.erase(m_pPlayerFire.begin() + i);
					m_pPlayerFire.shrink_to_fit();

					break;
				}
			}
		}
	}

	// Player VS Enemies collision
	if (m_pEnemy.size() > 0)
	{
		for (unsigned i = 0; i < m_pEnemy.size(); i++)
		{
			SDL_Rect tempH = { int(m_pHuman->getTransform()->position.x), int(m_pHuman->getTransform()->position.y),
						m_pHuman->getWidth(), m_pHuman->getHeight() };
			SDL_Rect tempE = { int(m_pEnemy[i]->getTransform()->position.x), int(m_pEnemy[i]->getTransform()->position.y),
						m_pEnemy[i]->getWidth(), m_pEnemy[i]->getHeight() };

			if (CollisionManager::AABBCheck(&tempH, &tempE))
			{
				m_pHuman->SetIsColliding(false);
				m_pHuman->Hit();
				SoundManager::Instance().playSound("collision", 0, -1);
				m_pDeath.push_back(new Death());
				m_pDeath.shrink_to_fit();
				m_pDeath[m_pDeath.size() - 1]->getTransform()->position = m_pEnemy[i]->getTransform()->position;
				addChild(m_pDeath[m_pDeath.size() - 1], 1, 4);

				

				removeChild(m_pEnemy[i]);
				m_pEnemy[i] = nullptr;
				m_pEnemy.erase(m_pEnemy.begin() + i);
				m_pEnemy.shrink_to_fit();

				HumanLife::m_hit();
			}
			else
			{
				m_pHuman->SetIsColliding(false);
			}
		}
	}
	if (isAlive && HumanLife::getHumanLife() <= 0)
	{
		//TODO: sound effect for player death

		playTimeSec = 5000;
		playTimeMint = 0;
		isAlive = false;
		//TheGame::Instance().changeSceneState(END_SCENE);
	}

	// PlayerFire VS Enemies
	if (m_pEnemy.size() > 0 && m_pPlayerFire.size() > 0)
	{
		for (unsigned i = 0; i < m_pPlayerFire.size(); i++)
		{
			for (unsigned j = 0; j < m_pEnemy.size(); j++)
			{
				SDL_Rect tempF = { int(m_pPlayerFire[i]->getTransform()->position.x), int(m_pPlayerFire[i]->getTransform()->position.y),
						m_pPlayerFire[i]->getWidth(), m_pPlayerFire[i]->getHeight() };
				SDL_Rect tempE = { int(m_pEnemy[j]->getTransform()->position.x)-16, int(m_pEnemy[j]->getTransform()->position.y),
							m_pEnemy[j]->getWidth()/2, m_pEnemy[j]->getHeight()/2 };

				if (CollisionManager::AABBCheck(&tempF, &tempE))
				{
					m_pDeath.push_back(new Death());
					m_pDeath.shrink_to_fit();
					m_pDeath[m_pDeath.size() - 1]->getTransform()->position = m_pEnemy[i]->getTransform()->position;
					addChild(m_pDeath[m_pDeath.size() - 1], 1, 4);

					removeChild(m_pEnemy[j]);
					m_pEnemy[j] = nullptr;
					m_pEnemy.erase(m_pEnemy.begin() + j);
					m_pEnemy.shrink_to_fit();

					SoundManager::Instance().playSound("enemydeath", 0, -1);

					removeChild(m_pPlayerFire[i]);
					m_pPlayerFire[i] = nullptr;
					m_pPlayerFire.erase(m_pPlayerFire.begin() + i);
					m_pPlayerFire.shrink_to_fit();

					break;
				}
			}

		}
	}

	// Player VS Diamond
	if (m_pDiamond.size() > 0)
	{
		for (unsigned i = 0; i < m_pDiamond.size(); i++)
		{
			SDL_Rect tempH = { int(m_pHuman->getTransform()->position.x), int(m_pHuman->getTransform()->position.y),
						m_pHuman->getWidth(), m_pHuman->getHeight() };
			SDL_Rect tempD = { int(m_pDiamond[i]->getTransform()->position.x)+16, int(m_pDiamond[i]->getTransform()->position.y)+16,
						m_pDiamond[i]->getWidth(), m_pDiamond[i]->getHeight() };

			if (CollisionManager::AABBCheck(&tempH, &tempD))
			{
				SoundManager::Instance().playSound("diamond", 0, -1);
				removeChild(m_pDiamond[i]);
				m_pDiamond[i] = nullptr;
				m_pDiamond.erase(m_pDiamond.begin() + i);
				m_pDiamond.shrink_to_fit();
			}

		}
	}

	// Player VS BulletSpawn
	if (m_pBullets.size() > 0)
	{
		for (unsigned i = 0; i < m_pBullets.size(); i++)
		{
			SDL_Rect tempH = { int(m_pHuman->getTransform()->position.x), int(m_pHuman->getTransform()->position.y),
						m_pHuman->getWidth(), m_pHuman->getHeight() };
			SDL_Rect tempD = { int(m_pBullets[i]->getTransform()->position.x) + 16, int(m_pBullets[i]->getTransform()->position.y) + 16,
						m_pBullets[i]->getWidth(), m_pBullets[i]->getHeight() };

			if (CollisionManager::AABBCheck(&tempH, &tempD))
			{
				// add Bullet to player's Bullets  
				sizeOfBulletArr = m_pBulletArray.size();
				m_pBulletArray.push_back(new Bullet(SDL_Rect{ sizeOfBulletArr * 32 + 10, 65, 32,32 }));
				m_pBulletArray.shrink_to_fit();
				addChild(m_pBulletArray[m_pBulletArray.size() - 1], 5, 1);

				SoundManager::Instance().playSound("diamond", 0, -1);

				// remove bullet spawn from level design
				removeChild(m_pBullets[i]);
				m_pBullets[i] = nullptr;
				m_pBullets.erase(m_pBullets.begin() + i);
				m_pBullets.shrink_to_fit();
			}

		}
	}

	// CountDown 10 minutes until gameover.
	//playTime -= TheGame::Instance().getDeltaTime()*1000.0f;
	playTimeSec -= TheGame::Instance().getDeltaTime() * 1000.0f;
	//std::cout << playTime <<"\n";
	//int time = (int)(playTime * 0.001f);
	int timeSec = (int)(playTimeSec * 0.001f);

	if(timeSec < 10)
	{
		m_pPlayTimeLabel->setText("Play Time: 0" + std::to_string(playTimeMint) + ":0" + std::to_string(timeSec));
	}
	else
	{
		m_pPlayTimeLabel->setText("Play Time: 0" + std::to_string(playTimeMint) + ":" + std::to_string(timeSec));
	}

	if (playTimeSec <= 0)
	{
		playTimeSec = 60000;
		playTimeMint -= 1;

		if(playTimeMint < 0)
		{
			TheGame::Instance().changeSceneState(END_SCENE);
		}
	}

	
	
	
	// CountDown 10 seconds until instruction text disappears.
	tutorialSec -= TheGame::Instance().getDeltaTime() * 1000.0f;
	int timeSecTutorial = (int)(tutorialSec * 0.001f);

	if (timeSecTutorial < 10)
	{
		m_pTutorialTimeLabel->setText("| W,A,S,D to move | SPACE to shoot | :" + std::to_string(timeSecTutorial));
	}
	else
	{
		m_pTutorialTimeLabel->setText("| W,A,S,D to move | SPACE to shoot | :" + std::to_string(timeSecTutorial));
	}

	if (timeSecTutorial == 0)
	{
		cout << "deleting tutorial" << endl;
	}

	if (tutorialSec <= 0)
	{
		tutorialSec = 10000;
		tutorialMint -= 1;
		if (tutorialMint < 0)
		{
			delete []m_pTutorialTimeLabel;
			cout << "deleting" << endl;
		}
	}

	
	
	
	// CountDown 10 seconds until bed instruction text disappears.
	bedTutorialSec -= TheGame::Instance().getDeltaTime() * 1000.0f;
	int bedTimeSecTutorial = (int)(bedTutorialSec * 0.001f);

	if (timeSecTutorial < 10)
	{
		m_pBedTutorialTimeLabel->setText("| Approach the bed... see what happens...| :" + std::to_string(bedTimeSecTutorial));
	}
	else
	{
		m_pBedTutorialTimeLabel->setText("| Approach the bed... see what happens...| :" + std::to_string(bedTimeSecTutorial));
	}

	if (bedTutorialSec <= 0)
	{
		bedTutorialSec = 10000;
		bedTutorialMint -= 1;
		if (bedTutorialMint < 0)
		{
			delete []m_pBedTutorialTimeLabel;
			cout << "deleting" << endl;
			//////////////////////////
			// Countdown till sprint instruction text disappears
			/*sprintTutorialSec -= TheGame::Instance().getDeltaTime() * 1000.0f;
			int sprintingTutorial = (int)(sprintTutorialSec * 0.001f);

			if (timeSecTutorial < 10)
			{
				m_pSprintTutorialTimeLabel->setText("| LEFT-SHIFT to sprint...You're gonna need it |");
			}
			else
			{
				m_pSprintTutorialTimeLabel->setText("| LEFT-SHIFT to sprint...You're gonna need it |");

			}

			if (sprintTutorialSec <= 0)
			{
				sprintTutorialSec = 10000;
				sprintTutorialMint -= 1;
				if (sprintTutorialMint < 0)
				{
					delete m_pSprintTutorialTimeLabel;
					cout << "deleting" << endl;
				}
			}*/
		}
	}



	// For counting the amount of Enemies
	if (m_pEnemy.size() > 0)
	{
		m_pCountEnemyLable->setText("X " + std::to_string(m_pEnemy.size()));
	}
	else if (m_pEnemy.size() == 0)
	{
		m_pCountEnemyLable->setText(" ");
	}

	updateDisplayList();

}

void PlayScene::clean()
{
	for (unsigned i = 0; i < m_pPlayerFire.size(); i++)
	{
		//delete m_pPlayerFire[i];
		m_pPlayerFire[i] = nullptr;
	}
	m_pPlayerFire.clear();
	m_pPlayerFire.shrink_to_fit();

	for (unsigned i = 0; i < m_pEnemy.size(); i++)
	{
		/*delete m_pEnemy[i];*/
		m_pEnemy[i] = nullptr;
	}
	m_pEnemy.clear();
	m_pEnemy.shrink_to_fit();

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

	for (unsigned i = 0; i < m_pBed.size(); i++)
	{
		delete m_pBed[i];
		m_pBed[i] = nullptr;
	}
	m_pBed.clear();
	m_pBed.shrink_to_fit();

	SDL_DestroyTexture(m_pCountEnemyT);
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	////////////// Player Movement [WASD] //////////////////////
	bool isSprint = EventManager::Instance().isKeyDown(SDL_SCANCODE_LSHIFT);

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
		CameraMovement(PLAYER_RUN_UP, isSprint);
	}
	else if (key == 'A')
	{
		CameraMovement(PLAYER_RUN_LEFT, isSprint);
	}
	else if (key == 'S')
	{
		CameraMovement(PLAYER_RUN_DOWN, isSprint);
	}
	else if (key == 'D')
	{
		CameraMovement(PLAYER_RUN_RIGHT, isSprint);
	}
	else
	{
		m_pHuman->setAnimationState(m_pHuman->getLastHumanDirection());
	}
	/////////////////////////////////////////////////////////////
	
	

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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P))
	{
		TheGame::Instance().changeSceneState(PAUSE_SCENE);
	}

	// To check Human lives
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_L))
	{
		m_HumanLife->setHumanLife(m_HumanLife->getHumanLife() - 1);
		SDL_Delay(100);
	}

	// To spawn Enemy for test
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_T))
	{
		m_pEnemy.push_back(new Enemy());
		m_pEnemy.shrink_to_fit();
		m_pEnemy[m_pEnemy.size() - 1]->setAnimationState(PLAYER_RUN_DOWN);
		m_pEnemy[m_pEnemy.size() - 1]->setLastEnemyDirection(PLAYER_RUN_DOWN);
		m_pEnemy[m_pEnemy.size() - 1]->getTransform()->position = glm::vec2{ m_pHuman->getTransform()->position.x + rand() % 300, m_pHuman->getTransform()->position.y + 200 };
		m_pEnemy[m_pEnemy.size() - 1]->setTargetPosition(m_pHuman->getTransform()->position);
		m_pEnemy[m_pEnemy.size() - 1]->getRigidBody()->acceleration = m_pEnemy[m_pEnemy.size() - 1]->getCurrentDirection() * m_pEnemy[m_pEnemy.size() - 1]->getAccelerationRate();
		m_pEnemy[m_pEnemy.size() - 1]->setEnabled(true);
		addChild(m_pEnemy[m_pEnemy.size() - 1], 1, 3);
		SDL_Delay(200);
	}

	// To reload bullets for test
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_R))
	{
		sizeOfBulletArr = m_pBulletArray.size();
		m_pBulletArray.push_back(new Bullet(SDL_Rect{ sizeOfBulletArr * 32 + 10, 65, 32,32 }));
		m_pBulletArray.shrink_to_fit();
		addChild(m_pBulletArray[m_pBulletArray.size() - 1], 5, 1);
		SDL_Delay(100);
	}

	////////////// SHOOTING //////////////////////
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		Shooting();
	}
	else
	{
		firing = false;
	}
	//////////////////////////////////////////////
}

void PlayScene::start()
{
	const SDL_Color gainsboro = { 220, 220, 220, 255 };
	m_setGridColliderEnabled(false);

	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Game Level
	m_pLevel = new Level();
	addChild(m_pLevel, 0, 0);

	initTileLocation();

	m_pPlayerFire.reserve(4);
	m_pEnemy.reserve(4);

	// Human Sprite
	m_pHuman = new Human();
	m_pHuman->setAnimationSpeed(0.3);
	addChild(m_pHuman, 1, 1);

	// Ghost 
	m_pGhost = new Ghost();
	m_pGhost->getTransform()->position = m_pHuman->getTransform()->position;
	m_pGhost->setLayerIndex(0);
	addChild(m_pGhost, 2, 2);  // addChild( GameObject, layerIndex, OrderIndex) 

	//Life
	m_HumanLife = new HumanLife();
	addChild(m_HumanLife, 3, 0);

	// Count Enemy
	m_pCountEnemyT = IMG_LoadTexture(Renderer::Instance().getRenderer(), "../Assets/sprites/Enemy.png");
	m_pCountEnemyLable = new Label("X ", "Consolas", 40, gainsboro, glm::vec2(850.0f, 40.0f));
	m_pCountEnemyLable->setParent(this);
	addChild(m_pCountEnemyLable,3,1);

	// Time ** NEED TO BE FIXED **
	//playTime = PLAY_TIME;
	playTimeMint = 5;
	playTimeSec = 60000;
	float fontSize = 35.0f;
	m_pPlayTimeLabel = new Label("Play Time", "Consolas", fontSize, gainsboro, glm::vec2(WIDTH * 0.5f, fontSize *0.5f + 20.0f));
	m_pPlayTimeLabel->setParent(this);
	addChild(m_pPlayTimeLabel, 3, 1);

	// time for movement tutorial
	tutorialMint = 1;
	tutorialSec = 1000;
	float tutorialFontSize = 20.0f;
	m_pTutorialTimeLabel = new Label("Use W,A,S,D to move, and press SPACE to shoot", "Consolas",
		tutorialFontSize, gainsboro, glm::vec2(WIDTH * 0.5f, 650.0f));
	m_pTutorialTimeLabel->setParent(this);
	addChild(m_pTutorialTimeLabel, 3, 1);

	// time for bed feature tutorial
	bedTutorialMint = 1;
	bedTutorialSec = 1000;
	float bedTutorialFontSize = 20.0f;
	m_pBedTutorialTimeLabel = new Label("Approach the bed... something might just pop out", "Consolas",
		bedTutorialFontSize, gainsboro, glm::vec2(WIDTH * 0.5f, 700.0f));
	m_pBedTutorialTimeLabel->setParent(this);
	addChild(m_pBedTutorialTimeLabel, 3, 1);

	// time for sprint tutorial 
	//sprintTutorialMint = 1;
	//sprintTutorialSec = 1000;
	//float sprintTutorialFontSize = 20.0f;
	//m_pSprintTutorialTimeLabel = new Label(" LEFT-SHIFT to sprint... You're gonna need it...", "Consolas",
	//	sprintTutorialFontSize, gainsboro, glm::vec2(WIDTH * 0.5f, 700.0f));
	//m_pSprintTutorialTimeLabel->setParent(this);
	//addChild(m_pSprintTutorialTimeLabel, 3, 1);

	//Death Animation
	/*m_pDeath.push_back(new Death());
	m_pDeath[0]->getTransform()->position = glm::vec2{ WIDTH / 2 - 50, HEIGHT / 2 - 50 };
	addChild(m_pDeath[0], 6, 4);*/

	// Bullet Available
	sizeOfBulletArr = m_pBulletArray.size();
	m_pBulletArray.push_back(new Bullet(SDL_Rect{ sizeOfBulletArr * 32 + 10, 65, 32,32 }));
	m_pBulletArray.shrink_to_fit();
	addChild(m_pBulletArray[m_pBulletArray.size() - 1], 5, 1);

	// Pause Button
	m_pPauseButton = new Button("../Assets/textures/pauseButton.png", "pauseButton", RESUME_BUTTON);
	m_pPauseButton->getTransform()->position = glm::vec2(WIDTH - 50, 50);
	m_pPauseButton->addEventListener(CLICK, [&]()-> void
		{
			m_pPauseButton->setActive(false);
			TheGame::Instance().changeSceneState(PAUSE_SCENE);
		});

	m_pPauseButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pPauseButton->setAlpha(128);
		});

	m_pPauseButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pPauseButton->setAlpha(255);
		});
	addChild(m_pPauseButton, 5, 0);

	// For event
	TextureManager::Instance().load("../Assets/textures/box.png", "box");
	SoundManager::Instance().load("../Assets/audio/coin3.wav", "diamond", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/collision.aiff", "collision", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/enemydeath.wav", "enemydeath", SOUND_SFX);

	m_pPlaySceneMusic = Mix_LoadMUS("../Assets/Audio/Night of the Streets5.mp3");
	m_pGunSound = Mix_LoadWAV("../Assets/Audio/LaserSFX.mp3");
	Mix_PlayMusic(m_pPlaySceneMusic,-1);
	isAlive = true;
	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::CameraMovement(PlayerAnimationState p, bool isSprint)
{
	m_pHuman->setAnimationState(p);
	m_pHuman->setLastHumanDirection(p);

	double speed = PLAYERSPEED;
	if (isSprint)
	{
		speed = speed * 2;
		m_pHuman->setAnimationSpeed(0.5);
	}
	else
	{
		speed = PLAYERSPEED;
		m_pHuman->setAnimationSpeed(0.3);
	}

	if (p == PLAYER_RUN_LEFT)
	{
		if (!checkLeftSensor())
		{
			m_pLevel->getTransform()->position.x += speed;
			for (int i = 0; i < tileLocation.size(); i++)
			{
				tileLocation[i]->x += speed;
			}
			for (Weap* w : m_pPlayerFire)
			{
				w->getTransform()->position.x += speed;
			}
			for (Enemy* e : m_pEnemy)
			{
				e->getTransform()->position.x += speed;
			}
			for (Diamond* d : m_pDiamond)
			{
				d->getTransform()->position.x += speed;
			}
			for (Bed* bed : m_pBed)
			{
				bed->positionAndSize.x += speed;
			}
			for (Obstacle* o : m_pObstacle)
			{
				o->positionAndSize.x += speed;
			}
			for (Death* d : m_pDeath)
			{
				d->getTransform()->position.x += speed;
			}
			for (Bullet* b : m_pBullets)
			{
				b->getTransform()->position.x += speed;
			}
		}
	}

	if (p == PLAYER_RUN_RIGHT)
	{
		if (!checkRightSensor())
		{
			m_pLevel->getTransform()->position.x -= speed;
			for (int i = 0; i < tileLocation.size(); i++)
			{
				tileLocation[i]->x -= speed;
			}
			for (Weap* w : m_pPlayerFire)
			{
				w->getTransform()->position.x -= speed;
			}
			for (Enemy* e : m_pEnemy)
			{
				e->getTransform()->position.x -= speed;
			}
			for (Diamond* d : m_pDiamond)
			{
				d->getTransform()->position.x -= speed;
			}
			for (Bed* bed : m_pBed)
			{
				bed->positionAndSize.x -= speed;
			}
			for (Obstacle* o : m_pObstacle)
			{
				o->positionAndSize.x -= speed;
			}
			for (Death* d : m_pDeath)
			{
				d->getTransform()->position.x -= speed;
			}
			for (Bullet* b : m_pBullets)
			{
				b->getTransform()->position.x -= speed;
			}
		}
	}

	if (p == PLAYER_RUN_UP)
	{
		if (!checkUpSensor())
		{
			m_pLevel->getTransform()->position.y += speed;
			for (int i = 0; i < tileLocation.size(); i++)
			{
				tileLocation[i]->y += speed;
			}
			for (Weap* w : m_pPlayerFire)
			{
				w->getTransform()->position.y += speed;
			}
			for (Enemy* e : m_pEnemy)
			{
				e->getTransform()->position.y += speed;
			}
			for (Diamond* d : m_pDiamond)
			{
				d->getTransform()->position.y += speed;
			}
			for (Bed* bed : m_pBed)
			{
				bed->positionAndSize.y += speed;
			}
			for (Obstacle* o : m_pObstacle)
			{
				o->positionAndSize.y += speed;
			}
			for (Death* d : m_pDeath)
			{
				d->getTransform()->position.y += speed;
			}
			for (Bullet* b : m_pBullets)
			{
				b->getTransform()->position.y += speed;
			}
		}
	}

	if (p == PLAYER_RUN_DOWN)
	{
		if (!checkDownSensor())
		{
			m_pLevel->getTransform()->position.y -= speed;
			for (int i = 0; i < tileLocation.size(); i++)
			{
				tileLocation[i]->y -= speed;
			}
			for (Weap* w : m_pPlayerFire)
			{
				w->getTransform()->position.y -= speed;
			}
			for (Enemy* e : m_pEnemy)
			{
				e->getTransform()->position.y -= speed;
			}
			for (Diamond* d : m_pDiamond)
			{
				d->getTransform()->position.y -= speed;
			}
			for (Bed* bed : m_pBed)
			{
				bed->positionAndSize.y -= speed;
			}
			for (Obstacle* o : m_pObstacle)
			{
				o->positionAndSize.y -= speed;
			}
			for (Death* d : m_pDeath)
			{
				d->getTransform()->position.y -= speed;
			}
			for (Bullet* b : m_pBullets)
			{
				b->getTransform()->position.y -= speed;
			}
		}
	}

	
}

void PlayScene::Shooting()
{
	//if (!firing && m_pIndicatorB->getAmountBullets() > 0)
	if (!firing && m_pBulletArray.size() > 0)
	{
		removeChild(m_pBulletArray[m_pBulletArray.size() - 1]);
		m_pBulletArray[m_pBulletArray.size() - 1] = nullptr;
		m_pBulletArray.erase(m_pBulletArray.begin() + m_pBulletArray.size() - 1);
		m_pBullets.shrink_to_fit();
		

		Mix_PlayChannel(-1, m_pGunSound, 0);
		m_pPlayerFire.push_back(new Weap(int(m_pHuman->getTransform()->position.x), int(m_pHuman->getTransform()->position.y) + 4, m_pHuman->getLastHumanDirection()));
		//m_pPlayerFire.push_back(new Weap(WIDTH / 2, HEIGHT / 2, m_pHuman->getLastHumanDirection()));
		m_pPlayerFire.shrink_to_fit();
		addChild(m_pPlayerFire[m_pPlayerFire.size() - 1], 1, 0);
		firing = true;
	}
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

	///////////// Spawn Enemy or Diamond when player touch the bed
	for (Bed* bed : m_pBed)
	{
		if (CollisionManager::AABBCheck(m_pHuman->upSenRect, &bed->getPosSize()))
		{
			if (!bed->getIsVisited())
			{
				bed->setIsVisited(true);
				spawn();
			}
			return true;
		}
	}

	for (Obstacle* o : m_pObstacle)
	{
		if (CollisionManager::AABBCheck(m_pHuman->upSenRect, &o->getPosSize()))
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

	///////////// Spawn Enemy or Diamond when player touch the bed
	for (Bed* bed : m_pBed)
	{
		if (CollisionManager::AABBCheck(m_pHuman->downSenRect, &bed->getPosSize()))
		{
			if (!bed->getIsVisited())
			{
				bed->setIsVisited(true);
				spawn();
			}
			return true;
		}
	}


	for (Obstacle* o : m_pObstacle)
	{
		if (CollisionManager::AABBCheck(m_pHuman->downSenRect, &o->getPosSize()))
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

	///////////// Spawn Enemy or Diamond when player touch the bed
	for (Bed* bed : m_pBed)
	{
		if (CollisionManager::AABBCheck(m_pHuman->rightSenRect, &bed->getPosSize()))
		{
			if (!bed->getIsVisited())
			{
				bed->setIsVisited(true);
				spawn();
			}
			return true;
		}
	}

	for (Obstacle* o : m_pObstacle)
	{
		if (CollisionManager::AABBCheck(m_pHuman->rightSenRect, &o->getPosSize()))
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

	///////////// Spawn Enemy or Diamond when player touch the bed
	for (Bed* bed : m_pBed)
	{
		if (CollisionManager::AABBCheck(m_pHuman->leftSenRect, &bed->getPosSize()))
		{
			if (!bed->getIsVisited())
			{
				bed->setIsVisited(true);
				spawn();
			}
			return true;
		}
	}


	for (Obstacle* o : m_pObstacle)
	{
		if (CollisionManager::AABBCheck(m_pHuman->leftSenRect, &o->getPosSize()))
		{
			return true;
		}
	}

	return false;
}

void PlayScene::spawn()
{
	// TODO: add sound effect player bed collision
	int randomAction = rand() % 2;
	if (numOfEnemySpawn > 6 || numOfBulletSpawn == 0) // this to make sure first spawn is bullet and maximum 7 enemies spawn
	{
		randomAction = 0;
	}
	if(numOfBulletSpawn > 7) // Maximum 8 bullets spawn
	{
		randomAction = 1;
	}
	if (randomAction == 0)
	{
		numOfBulletSpawn++;
		const SDL_Rect temp = { m_pHuman->getTransform()->position.x + rand() % 50, m_pHuman->getTransform()->position.y + 100, 32,32 };
		m_pBullets.push_back(new Bullet(temp));
		m_pBullets.shrink_to_fit();
		addChild(m_pBullets[m_pBullets.size() - 1], 2, 1);
	}
	else if (randomAction == 1)
	{
		numOfEnemySpawn++;
		m_pEnemy.push_back(new Enemy());
		m_pEnemy.shrink_to_fit();
		m_pEnemy[m_pEnemy.size() - 1]->setAnimationState(PLAYER_RUN_DOWN);
		m_pEnemy[m_pEnemy.size() - 1]->setLastEnemyDirection(PLAYER_RUN_DOWN);
		m_pEnemy[m_pEnemy.size() - 1]->getTransform()->position = glm::vec2{ m_pHuman->getTransform()->position.x + rand() % 300, m_pHuman->getTransform()->position.y + 200 };
		m_pEnemy[m_pEnemy.size() - 1]->setTargetPosition(m_pHuman->getTransform()->position);
		m_pEnemy[m_pEnemy.size() - 1]->getRigidBody()->acceleration = m_pEnemy[m_pEnemy.size() - 1]->getCurrentDirection() * m_pEnemy[m_pEnemy.size() - 1]->getAccelerationRate();
		m_pEnemy[m_pEnemy.size() - 1]->setEnabled(true);
		addChild(m_pEnemy[m_pEnemy.size() - 1], 1, 3);
		
	}
}

void PlayScene::initTileLocation()
{
	int xLocation = m_pLevel->getTransform()->position.x - m_pLevel->getWidth() / 2;
	int yLocation = m_pLevel->getTransform()->position.y - m_pLevel->getHeight() / 2;
	//int xLocOnMap[] = {10, 11, 12, 13, 14, 15}; // we need to add all the location of the walls on the map
	//int yLocOnMap[] = {78, 78, 78, 78, 78, 78 }; // we need to add all the location of the walls on the map

	////Event Tiles
	//tileLocation.push_back(new SDL_Rect{ 20 * 32 - xLocation, 82 * 32 + yLocation, 32, 32 });
	//tileLocation.push_back(new SDL_Rect{ 14 * 32 - xLocation, 82 * 32 + yLocation, 32, 32 });
	
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
			localLocation.push_back(SDL_Point{ i, 77 });
			localLocation.push_back(SDL_Point{ i, 76 });
		}
	}

	// Secont horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 14 && i != 15 && i != 16 && i != 17 && i != 57 && i != 58 && i != 59 && i != 60 && i != 81 && i != 82 && i != 83 && i != 84)
		{
			localLocation.push_back(SDL_Point{ i, 65 });
			localLocation.push_back(SDL_Point{ i, 64 });
			localLocation.push_back(SDL_Point{ i, 63 });
		}
	}

	// Third horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 49 && i != 50 && i != 51 && i != 52 && i != 66 && i != 67 && i != 68 && i != 69)
		{
			localLocation.push_back(SDL_Point{ i, 56 });
			localLocation.push_back(SDL_Point{ i, 57 });
			localLocation.push_back(SDL_Point{ i, 58 });
		}
	}

	// Forth horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 11 && i != 12 && i != 13 && i != 14 && i != 23 && i != 24 && i != 25 && i != 26 && i != 36 && i != 37 && i != 38 && i != 39 && i != 82 && i != 83 && i != 84 && i != 85)
		{
			localLocation.push_back(SDL_Point{ i, 42 });
			localLocation.push_back(SDL_Point{ i, 43 });
			localLocation.push_back(SDL_Point{ i, 44 });
		}
	}

	// Fifth horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 23 && i != 24 && i != 25 && i != 26 && i != 57 && i != 58 && i != 59 && i != 60 && i != 78 && i != 79 && i != 80 && i != 81)
		{
			localLocation.push_back(SDL_Point{ i, 30 });
			localLocation.push_back(SDL_Point{ i, 31 });
			localLocation.push_back(SDL_Point{ i, 32 });
		}
	}

	// Sixth horizontal wall from bottom
	for (int i = 10; i <= 89; i++)
	{
		if (i != 30 && i != 31 && i != 32 && i != 33 && i != 49 && i != 50 && i != 51 && i != 52 && i != 82 && i != 83 && i != 84 && i != 85)
		{
			localLocation.push_back(SDL_Point{ i, 23 });
			localLocation.push_back(SDL_Point{ i, 24 });
			localLocation.push_back(SDL_Point{ i, 25 });
		}
	}

	// First group of vertical walls 
	for (int i = 79; i <= 89; i++)
	{
		localLocation.push_back(SDL_Point{ 41, i });
		localLocation.push_back(SDL_Point{ 78, i });
		if (i != 84 && i != 85 && i != 86 && i != 87)
		{
			localLocation.push_back(SDL_Point{ 60, i });
			localLocation.push_back(SDL_Point{ 25, i });
		}
	}

	// Second group of vertical walls 
	for (int i = 66; i <= 75; i++)
	{
		localLocation.push_back(SDL_Point{ 49, i });
		localLocation.push_back(SDL_Point{ 70, i });
		if (i != 70 && i != 71 && i != 72 && i != 73)
		{
			localLocation.push_back(SDL_Point{ 25, i });
		}
	}

	// Third group of vertical walls 
	for (int i = 45; i <= 55; i++)
	{
		localLocation.push_back(SDL_Point{ 60, i });
		localLocation.push_back(SDL_Point{ 76, i });
		if (i != 49 && i != 50 && i != 51 && i != 52)
		{
			localLocation.push_back(SDL_Point{ 31, i });
			localLocation.push_back(SDL_Point{ 44, i });
		}
	}

	// Forth group of vertical walls 
	for (int i = 33; i <= 41; i++)
	{
		localLocation.push_back(SDL_Point{ 18, i });
		localLocation.push_back(SDL_Point{ 31, i });
		localLocation.push_back(SDL_Point{ 50, i });
		localLocation.push_back(SDL_Point{ 68, i });
		
	}

	// Fifth group of vertical walls 
	for (int i = 12; i <= 23; i++)
	{
		localLocation.push_back(SDL_Point{ 41, i });
		localLocation.push_back(SDL_Point{ 61, i });
		if (i != 16 && i != 17 && i != 18 && i != 19)
		{
			localLocation.push_back(SDL_Point{ 24, i });
			localLocation.push_back(SDL_Point{ 77, i });
		}
	}

	for (int i = 0; i < localLocation.size(); i++)
	{
		tileLocation.push_back(new SDL_Rect{ localLocation[i].x * 32 - xLocation, localLocation[i].y * 32 + yLocation, 32,32 });
	}

	// these lines to locate the double bed starting location
	bedPointLocation.push_back(SDL_Point{ 15, 79 });
	bedPointLocation.push_back(SDL_Point{ 68, 79 });
	bedPointLocation.push_back(SDL_Point{ 38, 66 });
	bedPointLocation.push_back(SDL_Point{ 67, 45 });
	bedPointLocation.push_back(SDL_Point{ 68, 12 });
	bedPointLocation.push_back(SDL_Point{ 50, 12 });
	bedPointLocation.push_back(SDL_Point{ 31, 12 });

	for (SDL_Point bed : bedPointLocation)
	{
		m_pBed.push_back(new Bed(SDL_Rect{ bed.x * 32 - xLocation, bed.y * 32 + yLocation, 32 * 3,32 * 2 }));
		m_pBed.shrink_to_fit();
	}
	
	bedPointLocation.clear();
	
	// these lines to locate the single bed starting location
	bedPointLocation.push_back(SDL_Point{ 45, 79 });
	bedPointLocation.push_back(SDL_Point{ 75, 66 });
	bedPointLocation.push_back(SDL_Point{ 50, 45 });
	bedPointLocation.push_back(SDL_Point{ 56, 45 });
	bedPointLocation.push_back(SDL_Point{ 86, 33 });
	bedPointLocation.push_back(SDL_Point{ 72, 33 });
	bedPointLocation.push_back(SDL_Point{ 45, 33 });
	bedPointLocation.push_back(SDL_Point{ 35, 33 });
	
	for (SDL_Point bed : bedPointLocation)
	{
		m_pBed.push_back(new Bed(SDL_Rect{ bed.x * 32 - xLocation, bed.y * 32 + yLocation, 32 * 2,32 * 2 }));
		m_pBed.shrink_to_fit();
	}

	//////////Obstacle/////////////
	SDL_Rect obstacleLocation[] = { {14, 71, 5, 2},
								    {38, 71, 3, 2},
								    {57, 70, 6, 2},
								    {78, 70, 7, 2},
								    {82, 49, 4, 2} };
	for (auto o : obstacleLocation)
	{
		m_pObstacle.push_back(new Obstacle(SDL_Rect{ o.x * 32 - xLocation, o.y * 32 + yLocation - 15, o.w * 32, o.h * 32}));
	}
}

bool PlayScene::m_getGridColliderEnabled() const
{
	return m_isGridColliderEnabled;
}

void PlayScene::m_setGridColliderEnabled(const bool state)
{
	m_isGridColliderEnabled = state;
}

void PlayScene::GUI_Function()
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

	static bool toggle_grid = false;
	if (ImGui::Checkbox("Toggle Grid", &toggle_grid))
	{
		m_setGridColliderEnabled(toggle_grid);
	}

	ImGui::Separator();

	static bool GhostMode = true;
	if (ImGui::Checkbox("Ghost Mode", &GhostMode))
	{
		m_pGhost->setEnabled(GhostMode);
	}

	/*ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}*/
	
	
	ImGui::End();
}


