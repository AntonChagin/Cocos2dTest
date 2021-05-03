#pragma once
#include "CT_State.h"
#include "CT_Player.h"

// All states are singletones

class Idle : public CT_State<CT_Player>
{
private:
	Idle() {}
	Idle(const Idle&) = delete;
	Idle& operator=(const Idle&) = delete;

public:
	static Idle* Instance();
	void Enter(std::shared_ptr<CT_Player> pObject) override;
};

class Walk : public CT_State<CT_Player>
{
private:
	Walk() {}
	Walk(const Walk&) = delete;
	Walk& operator=(const Walk&) = delete;

public:
	static Walk* Instance();
	void Enter(std::shared_ptr<CT_Player> pObject) override;
	void Execute(std::shared_ptr<CT_Player> pObject, float deltaTime) override;
};

class Attack : public CT_State<CT_Player>
{
private:	
	Attack() {}
	Attack(const Walk&) = delete;
	Attack& operator=(const Walk&) = delete;

public:
	static Attack* Instance();
	void Enter(std::shared_ptr<CT_Player> pObject) override;
};

class ReadyForAttack : public CT_State<CT_Player> 
{
private:
	ReadyForAttack() {}
	ReadyForAttack(const ReadyForAttack&) = delete;
	ReadyForAttack& operator=(const ReadyForAttack&) = delete;

public:
	static ReadyForAttack* Instance();
	void Enter(std::shared_ptr<CT_Player> pObject) override;
};