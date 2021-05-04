#include "CT_FSM.h"
#include <vector>
#include <CT_Player.h>

template <class entity_type>
CT_FSM<entity_type>::CT_FSM(std::shared_ptr<entity_type> pOwner)
{
	owner = pOwner;
	currentState = NULL;
	globalState = NULL;
}

template <class entity_type>
CT_FSM<entity_type>::~CT_FSM()
{
	stateTable.clear();
}

template <class entity_type>
CT_State<entity_type>* CT_FSM<entity_type>::getCurrentState() const
{
	return currentState;
}

template <class entity_type>
void CT_FSM<entity_type>::ChangeState(CT_State<entity_type>* pNewState)
{
	if (currentState != NULL)
		currentState->Exit(owner);
	currentState = pNewState;
	currentState->Enter(owner);
}

template <class entity_type>
void CT_FSM<entity_type>::ChangeGlobalState(CT_State<entity_type>* pNewState)
{
	if (globalState != NULL)
		globalState->Exit(owner);
	globalState = pNewState;
	globalState->Enter(owner);
}

template <class entity_type>
void CT_FSM<entity_type>::Update(float deltaTime)
{
	for (auto it = stateTable.begin(); it != stateTable.end(); ++it)
	{
		if (it->isGlobal) {
			if (it->currentState == globalState)
			{
				if (it->condition())
				{
					ChangeGlobalState(it->newState);
				}
			}
		}
		else {
			if (it->currentState == currentState)
			{
				if (it->condition())
				{
					ChangeState(it->newState);
				}
			}
		}

	}

	if (globalState)
		globalState->Execute(owner, deltaTime);

	if (currentState)
		currentState->Execute(owner, deltaTime);
}

template <class entity_type>
bool CT_FSM<entity_type>::isInState(const CT_State<entity_type>& st) const
{
	if (typeid(*currentState) == typeid(st)) return true;
	return false;
}

template <class entity_type>
void CT_FSM<entity_type>::SetCurrentState(CT_State<entity_type>* s)
{
	currentState = s;
	s->Enter(owner);
}

template <class entity_type>
void CT_FSM<entity_type>::SetGlobalState(CT_State<entity_type>* s)
{
	globalState = s;
	s->Enter(owner);
}

template <class entity_type>
CT_State<entity_type>* CT_FSM<entity_type>::CurrentState() const
{
	return currentState;
}

template <class entity_type>
CT_State<entity_type>* CT_FSM<entity_type>::GlobalState() const
{
	return globalState;
}

template CT_FSM<CT_Player>;