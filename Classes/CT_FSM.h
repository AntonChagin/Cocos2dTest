#pragma once
#include "CT_State.h"
#include <vector>
#include <functional>

using funcPtr = typename std::function<bool()>;
template <class entity_type>
struct Table_Entry
{
	CT_State<entity_type>* currentState;
	funcPtr condition;
	CT_State<entity_type>* newState;
	bool isGlobal = false;
};

template <class entity_type>
class CT_FSM
{
   
private:
	std::shared_ptr<entity_type> owner;
	// current state for side activities like shooting
	CT_State<entity_type>* currentState;
	// global state for main activities like walking, jumping
	CT_State<entity_type>* globalState;

public:
	std::vector<Table_Entry<entity_type>> stateTable;
	CT_FSM(std::shared_ptr<entity_type> pOwner) :owner(pOwner),
		currentState(NULL), globalState(NULL)
	{}
	~CT_FSM() {
		stateTable.clear();
	}
    inline CT_State<entity_type>* getCurrentState() const { return currentState; }

	void SetCurrentState(CT_State<entity_type>* s) { currentState = s; s->Enter(owner); }
	void SetGlobalState(CT_State<entity_type>* s)	{ globalState = s;  s->Enter(owner); }

	void  ChangeState(CT_State<entity_type>* pNewState)
	{
		if (currentState != NULL)
			currentState->Exit(owner);	
		currentState = pNewState;	
		currentState->Enter(owner);	
	}

	void  ChangeGlobalState(CT_State<entity_type>* pNewState)
	{
		if (globalState != NULL)
			globalState->Exit(owner);		
		globalState = pNewState;	
		globalState->Enter(owner);	
	}

	void  Update(float deltaTime)
	{
		for each (auto entry in stateTable)
		{
			if (entry.isGlobal) {
				if (entry.currentState == globalState)
				{
					if (entry.condition())
					{
						ChangeGlobalState(entry.newState);					
					}
				}
			}
			else {
				if (entry.currentState == currentState)
				{
					if (entry.condition())
					{
						ChangeState(entry.newState);
					}
				}
			}
		
		}

		if (globalState)   
			globalState->Execute(owner, deltaTime);

		if (currentState) 
			currentState->Execute(owner, deltaTime);
		
	}

	bool  isInState(const CT_State<entity_type>& st)const
	{
		if (typeid(*currentState) == typeid(st)) return true;
		return false;
	}
	CT_State<entity_type>* CurrentState()  const { return currentState; }
	CT_State<entity_type>* GlobalState()   const { return globalState; }
};


