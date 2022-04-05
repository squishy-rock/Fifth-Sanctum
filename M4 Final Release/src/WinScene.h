#pragma once
#ifndef _WIN_SCENE_
#define _WIN_SCENE_

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "bg.h"

class WinScene final : public Scene
{
public:
	WinScene();
	~WinScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_pCongratulationMessage;
	Label* m_pQuitInstruction;
};

#endif //Defined _WIN_SCENE_