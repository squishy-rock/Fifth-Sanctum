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

private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
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
};

#endif /* defined (__PLAY_SCENE__) */