#pragma once
#ifndef __HumanLife__
#define __HumanLife__
#include "Sprite.h"

class HumanLife : public Sprite
{
public:
	HumanLife();
	~HumanLife();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;



	// setters
	static void setHumanLife(int l) { m_humanLife = l; }

	// getters
	static int getHumanLife() { return m_humanLife; }

	// human life
	static inline int m_humanLife;
	static inline int hitCount, maxCount;
	static void m_hit();

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};

#endif 