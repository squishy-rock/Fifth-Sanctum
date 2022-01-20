#include "Missile.h"


Missile::Missile(int x, int y, stateMissile s, stateDir direction) :m_src({ 200,0,14,14 }), m_frameCtr(0), m_frameMax(3),
	m_spriteIdx(0), m_spriteMax(1) // Initializers happen before body.
{ // Body considered assignment not initialization.
	m_dst = {x,y,m_src.w*1,m_src.h*1};
	state = s;
	dir = direction;
}

void Missile::Update()
{
	// Animate.
	///*if (m_frameCtr++ == m_frameMax)
	//{
	//	m_frameCtr = 0;
	//	if (++m_spriteIdx == m_spriteMax)
	//	{
	//		m_spriteIdx = 0;
	//	}
	//	m_src.x = 0 + m_src.w * m_spriteIdx;
	//}*/
	// Move.
	if (state == PLAYER)
	{
		switch (dir){
		case U:
			m_dst.y -= MOVESPEED;
			break;
		case D:
			m_dst.y += MOVESPEED;
			break;
		case R:
			m_dst.x += MOVESPEED;
			break;
		case L:
			m_dst.x -= MOVESPEED;
			break;
		default:
			break;
		}
		
	}
	if(state == ENEMY)
		m_dst.y += MOVESPEED * 0.5;
}
