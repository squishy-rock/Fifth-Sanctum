#include "Death.h"
#include "TextureManager.h"
#include "Game.h"

Death::Death()
{
	TextureManager::Instance().loadSpriteSheet(
		"../Assets/sprites/explosion.txt",
		"../Assets/sprites/explosion.png",
		"deathspritesheet");

	setSpriteSheet(TextureManager::Instance().getSpriteSheet("deathspritesheet"));

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	//setType(DEATH);
	getTransform()->position = glm::vec2(WIDTH / 2, HEIGHT / 2);

	m_buildAnimations();

	numAnim = 0;
}

Death::~Death()
= default;

void Death::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Death according to animation state
	
	TextureManager::Instance().playAnimation("deathspritesheet", getAnimation("explosion"),
		x, y, 0.5f, 0, 255, true);
		
	numAnim++;
	if (numAnim >= 30)
	{
		isDone = true;
	}
}

void Death::update()
{

}

void Death::clean()
{
}


void Death::m_buildAnimations()
{
	Animation exp = Animation();
	exp.name = "explosion";
	exp.frames.push_back(getSpriteSheet()->getFrame("death-0"));
	exp.frames.push_back(getSpriteSheet()->getFrame("death-1"));
	exp.frames.push_back(getSpriteSheet()->getFrame("death-2"));
	exp.frames.push_back(getSpriteSheet()->getFrame("death-3"));
	exp.frames.push_back(getSpriteSheet()->getFrame("death-4"));
	exp.frames.push_back(getSpriteSheet()->getFrame("death-5"));
	exp.frames.push_back(getSpriteSheet()->getFrame("death-6"));
	setAnimation(exp);

}
