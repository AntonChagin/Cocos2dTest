#pragma once
#include "CT_State.h"
#include <vector>
#include <functional>

template <class entity_type>
struct Table_Entry
{
	CT_State<entity_type>* currentState;
	typename std::function<bool()> condition;
	CT_State<entity_type>* newState;
	bool isGlobal = false;
};

template <class entity_type> class CT_FSM
{

private:
	std::shared_ptr<entity_type> owner;
	// current state for side activities like shooting
	CT_State<entity_type>* currentState;
	// global state for main activities like walking, jumping
	CT_State<entity_type>* globalState;

public:
	std::vector<Table_Entry<entity_type>> stateTable;
	CT_FSM(std::shared_ptr<entity_type> pOwner);
	~CT_FSM();
	CT_State<entity_type>* getCurrentState() const;

	void SetCurrentState(CT_State<entity_type>* s);
	void SetGlobalState(CT_State<entity_type>* s);
	CT_State<entity_type>* CurrentState()  const;
	CT_State<entity_type>* GlobalState()   const;

	void  ChangeState(CT_State<entity_type>* pNewState);
	void  ChangeGlobalState(CT_State<entity_type>* pNewState);

	void  Update(float deltaTime);

	bool  isInState(const CT_State<entity_type>& st)const;
};


