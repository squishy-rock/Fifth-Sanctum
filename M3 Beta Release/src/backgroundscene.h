#pragma once
#ifndef __BACKGROUND_SCENE__
#define __BACKGROUND_SCENE__

#include "DisplayObject.h"

class BackgroundScene final : public DisplayObject {
public:
	BackgroundScene();
	~BackgroundScene();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

};


#endif /* defined (__TARGET__) */