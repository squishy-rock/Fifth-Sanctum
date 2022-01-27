#include "Enemy.h"
#include <cstdlib>



Enemy::Enemy(int x, int y) :m_src({ 0,0,64,64 }), m_frameCtr(0), m_frameMax(6),
m_spriteIdx(0), m_spriteMin(0), m_spriteMax(6), m_state(IDLE2) // Initializers happen before body.
{ // Body considered assignment not initialization.
	m_dst = { x,y,m_src.w * 2,m_src.h * 2 };
	colume = 0;
	row = 1;
}

void Enemy::Update()
{
	// Animate.
	if (m_frameCtr++ == m_frameMax)
	{
		m_frameCtr = 0;
		if (++m_spriteIdx == m_spriteMax)
		{
			m_spriteIdx = m_spriteMin;
		}
		m_src.y = m_src.h * row ;
		m_src.x = m_src.w * m_spriteIdx;
	}
	// Move.
	// m_dst.y -= MOVESPEED;
	/*if (m_state == MOVED2 && m_dst.y < HEIGHT - 32 * 2) {
		m_dst.y += MOVESPEED;
	}
	else if (m_state == MOVEU2 && m_dst.y > 0) {
		m_dst.y -= MOVESPEED;
	}
	else if (m_state == MOVEL2 && m_dst.x > 0) {
		m_dst.x -= MOVESPEED;
	}
	else if (m_state == MOVER2 && m_dst.x < WIDTH - 32 * 2) {
		m_dst.x += MOVESPEED;
	}*/
	m_Move();
}

void Enemy::SetAnimation(stateE s, unsigned short min, unsigned short max)
{
	m_state = s;
	m_spriteIdx = m_spriteMin = min;
	m_spriteMax = max;
	m_frameCtr = 0;
	switch (s)
	{
		/*case IDLEN:
			colume = 0;
			break;*/
	case MOVER2:
		row = 3;
		break;
	case MOVEL2:
		row = 1;
		break;
	case MOVEU2:
		row = 0;
		break;
	case MOVED2:
		row = 2;
		break;
	default:
		break;
	}
}

void Enemy::setDestination(const SDL_Rect destination)
{
	m_destination = destination;
}

void Enemy::m_Move()
{
	m_targetDirection.x = m_destination.x - m_dst.x;
	m_targetDirection.y = m_destination.y - m_dst.y;

	m_dst.x += m_targetDirection.x * 0.008f;
	m_dst.y += m_targetDirection.y * 0.008f;
	
	if (m_targetDirection.x < 0 && m_targetDirection.y > 0 && m_state != MOVEL2)
	{
		SetAnimation(MOVEL2, 0, 6);
	}
	else if (m_targetDirection.x > 0 && m_targetDirection.y > 0 && m_state != MOVER2)
	{
		SetAnimation(MOVER2, 0, 6);
	}
	else if (m_targetDirection.y < 0 && m_state != MOVEU2)
	{
		SetAnimation(MOVEU2, 0, 6);
	}
	else if (m_targetDirection.x == 0 && m_targetDirection.y > 0 && m_state != MOVED2)
	{
		SetAnimation(MOVED2, 0, 6);
	}
	
}