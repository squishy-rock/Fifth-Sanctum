#pragma once
#ifndef __WEAPON1__
#define __WEAPON1__
#include "DisplayObject.h"
#include "Direction.h"
#include "Game.h"

class Weapon1 final : public DisplayObject
{
public:
	// constructors
	Weapon1();
	//Weapon1(int , int , Direction d);

	// destructor
	~Weapon1();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;

	void setBulletDir(Direction d);
	Direction getBulletDir();
private:
	Direction bulletDir = MRIGHT;

};

#endif /* defined (__WEAPON1__) */