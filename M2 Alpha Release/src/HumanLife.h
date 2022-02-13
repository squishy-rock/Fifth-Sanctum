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
	void setHumanLife(int l) { m_humanLife = l; }

	// getters
	int getHumanLife() { return m_humanLife; }

private:
	void m_move();
	void m_checkBounds();
	void m_reset();

	// human life
	int m_humanLife;

};

#endif 