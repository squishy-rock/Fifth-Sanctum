#pragma once
#ifndef __AGENT__
#define __AGENT__

#include <glm/vec4.hpp>
#include "DisplayObject.h"

class Agent : public DisplayObject
{
public:
	Agent();
	~Agent();

	// Inherited via GameObject
	void draw() override = 0;
	void update() override = 0;
	void clean() override = 0;

	// getters
	glm::vec2 getTargetPosition() const;
	glm::vec2 getCurrentDirection() const;
	float getLOSDistance() const;
	bool hasLOS() const;
	float getCurrentHeading() const;
	glm::vec4 getLOSColour() const;

	glm::vec2 getLeftLOSEndPoint() const;
	glm::vec2 getMiddleLOSEndPoint() const;
	glm::vec2 getRightLOSEndPoint() const;
	glm::vec2 getLeft2LOSEndPoint() const;
	glm::vec2 getRight2LOSEndPoint() const;
	bool* getCollisionWhisker(); // returns the entire array
	glm::vec4 getLineColour(int index);
	float getWhiskerAngle() const;

	// setters
	void setTargetPosition(glm::vec2 new_position);
	void setCurrentDirection(glm::vec2 new_direction);
	void setLOSDistance(float distance);
	void setHasLOS(bool state);
	void setCurrentHeading(float heading);
	void setLOSColour(glm::vec4 colour);

	void setLeftLOSEndPoint(glm::vec2 point);
	void setMiddleLOSEndPoint(glm::vec2 point);
	void setRightLOSEndPoint(glm::vec2 point);
	void setLeft2LOSEndPoint(glm::vec2 point);
	void setRight2LOSEndPoint(glm::vec2 point);
	void setLineColour(int index, glm::vec4 colour);
	void setWhiskerAngle(float angle);

	// public functinos
	void updateWhiskers(float angle);

private:
	void m_changeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

	// LOS
	float m_LOSDistance;
	bool m_hasLOS;
	glm::vec4 m_LOSColour;

	// Whiskers
	glm::vec2 m_leftLOSEndPoint;
	glm::vec2 m_middleLOSEndPoint;
	glm::vec2 m_rightLOSEndPoint;
	glm::vec2 m_left2LOSEndPoint;
	glm::vec2 m_right2LOSEndPoint;
	glm::vec4 m_lineColour[5]; // you will need to change this to 5 to support your whiskers
	bool m_collisionWhiskers[5]; // change to 5 - keeps track of each Whisker colliding

	float m_whiskerAngle; // angle of the left and right whiskers relative to the heading
};



#endif /* defined ( __AGENT__) */