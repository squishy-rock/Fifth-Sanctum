#pragma once
#ifndef _PLAYER_H_ // Portable. Oldschool. Better standard.
#define _PLAYER_H_
#include <SDL.h>
#include "Engine.h"
enum state { IDLE, MOVER, MOVEL, MOVEU, MOVED };


class Player
{
private:

	unsigned short m_frameCtr,  // Counts the number of frames. 
		m_frameMax,	// Number of frames each sprite is displayed. Animation speed.
		m_spriteIdx, // Which sprite to display.
		m_spriteMin, // Starting sprite index of animation.
		m_spriteMax; // Number of sprites in the animation.
	SDL_Rect playableArea;
public:
	state m_state; // State control value for animation.
	SDL_Rect m_src, m_dst;
	int colume;
	Player(int = 0, int = 0); // Default and non-default constructor.
	void Update();
	void SetAnimation(state, unsigned short, unsigned short);
};

#endif
