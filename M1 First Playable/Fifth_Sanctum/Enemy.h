
//#pragma once // Microsoft or .NET standard. Not that portable.
#ifndef _ENEMY_H_ // Portable. Oldschool. Better standard.
#define _ENEMY_H_
#include <SDL.h>
#include "Engine.h"
#include "Player.h"
#define MOVESPEED 3

//enum state2 { IDLE2, MOVE2 };
enum stateE { IDLE2, MOVER2, MOVEL2, MOVEU2, MOVED2 };
class Enemy
{
private:

	unsigned short m_frameCtr,  // Counts the number of frames. 
		m_frameMax,	// Number of frames each sprite is displayed. Animation speed.
		m_spriteIdx, // Which sprite to display.
		m_spriteMin, // Starting sprite index of animation.
		m_spriteMax; // Number of sprites in the animation.
	SDL_Rect m_destination;
	SDL_Rect m_targetDirection;
	void m_Move();

public:

	stateE m_state; // State control value for animation.
	SDL_Rect m_src, m_dst;
	int colume;
	int row;
	Enemy(int = 0, int = 0); // Default and non-default constructor.
	void Update();
	void SetAnimation(stateE, unsigned short, unsigned short);
	void setDestination(SDL_Rect destination);
};

#endif