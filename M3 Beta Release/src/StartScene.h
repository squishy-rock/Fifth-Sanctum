#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "SoundManager.h"
#include "Player.h"
#include "Human.h"
#include "StartBackground.h"





class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};

	Player* m_pPlayer;
	Human* m_pHuman;
	StartBackground* m_pStartBackground;


	Mix_Chunk* m_startButtonSFX;
	Mix_Music* m_titleTheme;
};

#endif /* defined (__START_SCENE__) */