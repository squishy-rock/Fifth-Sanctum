#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

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

	bool checkUpSensor();
	bool checkDownSensor();
	bool checkRightSensor();
	bool checkLeftSensor();

	void initTileLocation();

	bool m_getGridColliderEnabled() const;
	void m_setGridColliderEnabled(bool state);

private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	bool m_isGridColliderEnabled;
	glm::vec2 m_mousePosition;

	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	Human* m_pHuman;
	Ghost* m_pGhost;
	Level* m_pLevel;

	
	

	HumanLife* m_HumanLife;

	bool m_playerFacingRight;

	//Music and Sound
	Mix_Music* m_pPlaySceneMusic;
	Mix_Chunk* m_pGunSound;

	std::vector<SDL_Rect*> tileLocation;

	std::vector<SDL_Point> localLocation;
};

#endif /* defined (__PLAY_SCENE__) */