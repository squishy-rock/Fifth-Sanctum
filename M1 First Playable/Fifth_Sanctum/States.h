#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include <string>
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "Player.h"
#include "Missile.h"
#include <vector>
#include <map>
using namespace std;

// An abstract class is one that cannot be instantiated.
// Why? Because they'd be a base class most likely.
class State // This is an abstract base class for all states. (interface)
{
protected: // Private but inherited.
	State() {};
public: // Public methods.
	//virtual ~State() = default;
	virtual void Enter() = 0; // = 0 means pure virtual - must be define in subclass.
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume() { };
};


class TitleState : public State
{
private: // Private properties.
	// map for music track goes here.
	map<string, Mix_Music*> m_sounds;
	
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};
//
//class GameState : public State
//{
//private: // Private properties.
//	// map for sfx goes here.
//	map<string, Mix_Chunk*> m_sfx;
//	// map for music track goes here.
//	map<string, Mix_Music*> m_sounds;
//
//	SDL_Rect g_BG1;
//	SDL_Texture* g_pBGTexture; // For background.
//	SDL_Texture* g_pPlayerHumanTexture;
//	SDL_Texture* g_pPlayerWeaponTexture;
//	Player* g_player;
//	vector<Missile*> g_playerFire;
//	stateDir missileDirection;
//
//	Mix_Chunk* g_pMissile; // death.wav
//
//	SDL_Event event;
//public:
//	GameState();
//	virtual void Enter();
//	virtual void Update();
//	virtual void Render();
//	virtual void Exit();
//	virtual void Resume();
//};

// Add EndState here just like the others.
class EndState : public State
{
public:
	EndState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};
#endif