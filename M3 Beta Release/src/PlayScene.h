#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__
#include "Enemy.h"
#include "Obstacle.h"
#include "Weapon1.h"
#include "Weap.h"
#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Human.h"
#include "Ghost.h"
#include "Level.h"
#include "Button.h"
#include "Label.h"
#include "HumanLife.h"
#include "SoundManager.h"
#include "Diamond.h"
#include "Bed.h"
#include "Death.h"
#include "Bullet.h"
#include <vector>
#include <map>
#include <string>


class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void CameraMovement(PlayerAnimationState, bool);
	void Shooting();

	bool checkUpSensor();
	bool checkDownSensor();
	bool checkRightSensor();
	bool checkLeftSensor();

	void spawn();
	void gameOver();

	void initTileLocation();

	bool m_getGridColliderEnabled() const;
	void m_setGridColliderEnabled(bool state);

	bool CheckKeyList(char _c) {
		if (std::find(keyList.begin(), keyList.end(), _c) != keyList.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool DeleteKeyList(char _c) {
		bool _rtn = false;
		for (int i = 0; i < keyList.size(); ) {
			if (keyList[i] == _c) {
				keyList.erase(keyList.begin() + i);
				_rtn = true;
				break;
			}
			else {
				i++;
			}
		}
		return _rtn;
	}

private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	bool m_isGridColliderEnabled;
	glm::vec2 m_mousePosition;

	std::vector <Weap*> m_pPlayerFire;
	std::vector <char> keyList;

	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	Human* m_pHuman;
	Ghost* m_pGhost;
	Level* m_pLevel;

	bool firing = false;
	bool isAlive;

	bool m_playerFacingRight;

	//Music and Sound
	Mix_Music* m_pPlaySceneMusic;
	Mix_Chunk* m_pGunSound;

	std::vector<SDL_Rect*> tileLocation;
	std::vector<SDL_Point> localLocation;
	//std::vector<SDL_Rect*> bedLocation;
	std::vector<SDL_Point> bedPointLocation;

	std::vector<Enemy*> m_pEnemy;
	std::vector<Diamond*> m_pDiamond;
	std::vector<Bullet*> m_pBullets;
	std::vector<Bed*> m_pBed;
	std::vector<Obstacle*> m_pObstacle;
	std::vector<Death*> m_pDeath;
	int numOfEnemySpawn = 0;
	int numOfBulletSpawn = 0;
	// UI
	HumanLife* m_HumanLife;
	Label* m_pCountEnemyLable;
	SDL_Texture* m_pCountEnemyT;
	int numOfEnemiesKilled = 0;

	std::vector<Bullet*> m_pBulletArray;
	int sizeOfBulletArr;

	Button* m_pPauseButton;

	// Time
	float playTimeSec;
	int playTimeMint;
	float PLAY_TIME = 10 * 60 * 1000; // 10 * 60seconds * 1000ms
	Label* m_pPlayTimeLabel;

	// Tutorial for movement
	float tutorialTimeSec;
	//float TUTORIAL_TIME = 10 * 10 * 1000;
	Label* m_pTutorialTimeLabel;

	// Time for tutorial on bed feature
	Label* m_pBedTutorialTimeLabel;

	// Player
	int stamina;
	bool isSprint;
	Label* m_pStaminaLabel;

};

#endif /* defined (__PLAY_SCENE__) */