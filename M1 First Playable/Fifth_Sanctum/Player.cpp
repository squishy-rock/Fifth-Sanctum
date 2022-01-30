#include "Player.h"


Player::Player(int x, int y) :m_src({ 0,0,32,32 }), m_frameCtr(0), m_frameMax(5),
m_spriteIdx(0), m_spriteMin(0), m_spriteMax(1), m_state(IDLE) // Initializers happen before body.
{ // Body considered assignment not initialization.
	m_dst = { x,y,m_src.w * 2,m_src.h * 2 };
	m_spriteIdx = m_spriteMin;
	colume = 0;
	playableArea = { 100, 265, 830, 400 };
}

void Player::Update()
{
	// Animate.
	if (m_frameCtr++ == m_frameMax)
	{
		m_frameCtr = 0;
		if (++m_spriteIdx == m_spriteMax)
		{
			m_spriteIdx = m_spriteMin;
		}
		m_src.y = 0 + (m_src.w + 16) * m_spriteIdx;
		m_src.x = (m_src.w + 16) * colume;
	}
	// Move.
	// m_dst.y -= MOVESPEED;
	if (m_state == MOVED && m_dst.y < playableArea.y + playableArea.h - 32 * 2) {
		m_dst.y += SPEED;
	}
	else if (m_state == MOVEU && m_dst.y > playableArea.y - 32 * 2) {
		m_dst.y -= SPEED;
	}
	else if (m_state == MOVEL && m_dst.x > playableArea.x) {
		m_dst.x -= SPEED;
	}
	else if (m_state == MOVER && m_dst.x < playableArea.x + playableArea.w - 32 * 2) {
		m_dst.x += SPEED;
	}
}

void Player::SetAnimation(state s, unsigned short min, unsigned short max)
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
	case MOVER:
		colume = 3;
		break;
	case MOVEL:
		colume = 1;
		break;
	case MOVEU:
		colume = 2;
		break;
	case MOVED:
		colume = 0;
		break;
	default:
		break;
	}
}
