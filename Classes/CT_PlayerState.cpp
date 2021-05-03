#include "CT_PlayerState.h"
#include "CT_FSM.h"
#include <string>
USING_NS_CC;

// not thread safe!
Idle* Idle::Instance()
{
	static Idle instance;
	return &instance;
}

void Idle::Enter(std::shared_ptr<CT_Player> pObject)
{
    pObject->stopPressed = false;
    pObject->skeleton->stopAllActions();
    pObject->skeleton->setAnimation(0, "idle", true);
    pObject->skeleton->update(0.0f);
}

// not thread safe!
Walk* Walk::Instance()
{
	static Walk instance;

	return &instance;
}

void Walk::Enter(std::shared_ptr<CT_Player> pObject)
{
    pObject->destinationChanged = false;
    pObject->skeleton->stopAllActions();
    pObject->skeleton->setAnimation(0, "move", true);

    Vec2  currentDestination = pObject->destination;
    Vec2 currentPos = pObject->skeleton->getPosition(); 

    // flip skeleton image to show direction of moving
    if (currentPos.x > currentDestination.x)
        pObject->skeleton->getSkeleton()->flipX = 0;
    else
        pObject->skeleton->getSkeleton()->flipX = 1;
    pObject->skeleton->update(0.0f);

}

 void  Walk::Execute(std::shared_ptr<CT_Player> pObject, float deltaTime)
{
    Vec2  currentDestination = pObject->destination;
    float moveTime = deltaTime;
    float speed = pObject->speed * deltaTime;
    Vec2 currentPos = pObject->skeleton->getPosition();
    currentDestination -= currentPos;
    currentDestination.normalize();
    currentDestination = Vec2(currentDestination.x * speed, currentDestination.y * speed);
    pObject->skeleton->runAction(
        MoveBy::create(moveTime, currentDestination));
}

 // not thread safe!
Attack* Attack::Instance()
{
    static Attack instance;

    return &instance;
}

void Attack::Enter(std::shared_ptr<CT_Player> pObject)
{
    pObject->attackPressed = false;
    pObject->canAttack = false;

    pObject->skeleton->runAction(
        Sequence::create(
            CallFunc::create([=]() {
        // For not global activities we can use different tracks rather than default 0
                pObject->skeleton->setAnimation(1, "attack", false);
                pObject->skeleton->update(0.0f);
                pObject->skeleton->setCompleteListener([pObject](spTrackEntry* entry) {
                    std::string animName = entry->animation->name;

                    if (animName == "attack") {
                        pObject->canAttack = true;
                    }
                });
            }),
            NULL));
}

// not thread safe!
ReadyForAttack* ReadyForAttack::Instance()
{
    static ReadyForAttack instance;

    return &instance;
}

void ReadyForAttack::Enter(std::shared_ptr<CT_Player> pObject)
{
    pObject->skeleton->setCompleteListener(NULL);
    pObject->skeleton->setEmptyAnimation(1, 0.0f);
}
