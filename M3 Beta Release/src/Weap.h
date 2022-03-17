#pragma once
#ifndef __WEAP__
#define __WEAP__
#include "DisplayObject.h"
#include "Direction.h"
#include "PlayerAnimationState.h"

#define SPEED 8.0f

class Weap final : public DisplayObject
{
public:
	Weap();
	Weap(int x, int y, PlayerAnimationState d);
	~Weap();

	void setBulletDir(PlayerAnimationState d) { bulletDir = d; }
	PlayerAnimationState getBulletDir() { return bulletDir; }

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
private:
	PlayerAnimationState bulletDir;
};

#endif /* defined (__WEAP__) */

