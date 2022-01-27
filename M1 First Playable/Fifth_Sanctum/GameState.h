#pragma once
#ifndef _GAMESTATES_H_
#define _GAMESTATES_H_

#include "States.h"

class GameState : public State
{
private: // Private properties.
	// map for sfx goes here.
	map<string, Mix_Chunk*> m_sfx;
	// map for music track goes here.
	map<string, Mix_Music*> m_sounds;

	SDL_Rect g_BG1;
	SDL_Texture* g_pBGTexture; // For background.
	SDL_Texture* g_pPlayerHumanTexture;
	SDL_Texture* g_pPlayerWeaponTexture;
	Player* g_player;
	vector<Missile*> g_playerFire;
	stateDir missileDirection;

	//Mix_Chunk* g_pMissile; // death.wav

	SDL_Event event;

	bool firing;
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
};

#endif
