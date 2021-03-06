#pragma once
#ifndef __GAME_OBJECT_TYPE__
#define __GAME_OBJECT_TYPE__
enum GameObjectType {
	NONE = -1,
	AGENT,
	PATH_NODE,
	SPACE_SHIP,
	OBSTACLE,
	WEAPON1,
	SHIP,
	TARGET,
	GHOST,
	BED,
	LEVEL,
	PLAYER,
	HUMAN,
	ENEMY,
	PLANE,
	START_BUTTON,
	RESTART_BUTTON,
	BACK_BUTTON,
	NEXT_BUTTON,
	NUM_OF_TYPES,
	LIFE,
	RESUME_BUTTON,
	QUIT_BUTTON,
	ITEM
};
#endif /* defined (__GAME_OBJECT_TYPE__) */