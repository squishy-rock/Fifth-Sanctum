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
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};

	Human* m_pHuman;
	StartBackground* m_pStartBackground;

	std::vector <char> keyList;

	Mix_Chunk* m_startButtonSFX;
	Mix_Music* m_titleTheme;
};

#endif /* defined (__START_SCENE__) */