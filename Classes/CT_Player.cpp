#include "CT_Player.h"
#include <CT_PlayerState.h>

void CT_Player::init(std::shared_ptr<CT_Player> player)
{
	skeleton = spine::SkeletonAnimation::createWithJsonFile("anim/hero_butcher_mile/hero_butcher_mile.json", "anim/hero_butcher_mile/hero_butcher_mile.atlas");
	FSM = std::make_unique<CT_FSM<CT_Player>>(player);
	
	// Fill FSM table with rules:
	Table_Entry<CT_Player> fromIdleToWalk;
	fromIdleToWalk.currentState = Idle::Instance();
	fromIdleToWalk.newState = Walk::Instance();
	auto lambda_destinationChanged = [player]() {
		return player->destinationChanged;		
	};
	fromIdleToWalk.condition = lambda_destinationChanged;
	fromIdleToWalk.isGlobal = true;
	FSM->stateTable.push_back(fromIdleToWalk);

	Table_Entry<CT_Player> fromWalkToIdle;
	fromWalkToIdle.currentState = Walk::Instance();
	fromWalkToIdle.newState = Idle::Instance();
	auto lambda_stopNeeded = [player]() {
		if (player->stopPressed)
			return true;
		if (player->destination.distance(player->skeleton->getPosition()) < 1.0f)
			return true;
		return false;
	};
	fromWalkToIdle.condition = lambda_stopNeeded;
	fromWalkToIdle.isGlobal = true;
	FSM->stateTable.push_back(fromWalkToIdle);

	Table_Entry<CT_Player> fromWalkToWalk;
	fromWalkToWalk.currentState = Walk::Instance();
	fromWalkToWalk.newState = Walk::Instance();
	fromWalkToWalk.condition = lambda_destinationChanged;
	fromWalkToWalk.isGlobal = true;
	FSM->stateTable.push_back(fromWalkToWalk);

	Table_Entry<CT_Player> fromAttackToReady;
	fromAttackToReady.currentState = Attack::Instance();
	fromAttackToReady.newState = ReadyForAttack::Instance();
	auto lambda_canAttack = [player]() {
		return player->canAttack;
	};
	fromAttackToReady.condition = lambda_canAttack;
	fromAttackToReady.isGlobal = false;
	FSM->stateTable.push_back(fromAttackToReady);

	Table_Entry<CT_Player> fromReadyToAttack;
	fromReadyToAttack.currentState = ReadyForAttack::Instance();
	fromReadyToAttack.newState = Attack::Instance();
	auto lambda_needAttack = [player]() {
		return player->attackPressed;
	};
	fromReadyToAttack.condition = lambda_needAttack;
	fromReadyToAttack.isGlobal = false;
	FSM->stateTable.push_back(fromReadyToAttack);

	FSM->ChangeGlobalState(Idle::Instance());		

	FSM->ChangeState(ReadyForAttack::Instance());
}
