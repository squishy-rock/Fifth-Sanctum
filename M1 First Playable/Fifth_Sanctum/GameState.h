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
	SDL_Rect g_TutorialBox;
	SDL_Renderer* renderer;
	SDL_Texture* g_pBGTexture; // For background.
	SDL_Texture* g_pPlayerHumanTexture;
	SDL_Texture* g_pEnemyTexture;
	SDL_Texture* g_pPlayerWeaponTexture;
	SDL_Texture* g_pTutorialTexture; //To insert instruction for user
	SDL_Surface* g_pTutorialSurface;
	Player* g_player;
	vector<Missile*> g_playerFire;
	stateDir missileDirection;

	vector<Enemy*> g_enemy;
	stateDir enemyDir;
	vector<Missile*> g_enemyMissiles;

	SDL_Event event;

	bool firing;
	Timer* timerEnemySpawn;

	TTF_Font* font;
	SDL_Color color; 
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

	
};

#endif
