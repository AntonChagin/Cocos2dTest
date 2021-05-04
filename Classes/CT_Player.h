#pragma once
#include <cocos/editor-support/spine/SkeletonAnimation.h>
#include <cocos2d.h>
#include "CT_FSM.h"

class CT_Player
{

public: 
	CT_Player() {
		
	};

	void init(std::shared_ptr<CT_Player>);
	// Final State Machine
	std::unique_ptr <CT_FSM<CT_Player>> FSM;
	cocos2d::Vec2 destination;
	spine::SkeletonAnimation* skeleton;
	bool canAttack = true;
	bool destinationChanged = false;
	bool stopPressed = false;
	bool attackPressed = false;
	// speed in pixels/second
	float speed = 100.0f;
};

