#pragma once
#ifndef __PAUSE_SCENE__
#define __PAUSE_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "backgroundscene.h"

class PauseScene final : public Scene
{
public:
	PauseScene();
	~PauseScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_label{};
	Button* m_pResumeButton;
	Button* m_pRestartButton;
	Button* m_pQuitButton;
	BackgroundScene* m_pBackgroundScene;
};

#endif /* defined (__PAUSE_SCENE__)*/