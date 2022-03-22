#pragma once
#ifndef __INDICATORBULLET__
#define __INDICATORBULLET__
#include "Sprite.h"

class IndicatorBullet : public Sprite
{
public:
	IndicatorBullet();
	~IndicatorBullet();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;



	// setters
	static void setAmountBullets(int a) { m_amountBullets = a; }

	// getters
	static int getAmountBullets() { return m_amountBullets; }

	// amount of bullets
	static inline int m_amountBullets;

private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};

#endif 