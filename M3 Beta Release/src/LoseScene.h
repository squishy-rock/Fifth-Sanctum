#pragma once
#ifndef _LOSE_SCENE_
#define _LOSE_SCENE_
#endif // !_LOSE_SCENE_

#include "Scene.h"
#include "Label.h"
#include "Button.h"

class LoseScene final : public Scene
{
public:
	LoseScene();
	~LoseScene();

	//Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	
	Label* m_pLoseInstructions;
	Button* m_pRestartButton;
	Button* m_pQuitButton;
};

