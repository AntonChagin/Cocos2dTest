#pragma once
#include <memory>

template <class entity_type>
class CT_State
{
public:
	virtual ~CT_State();
	virtual void Enter(std::shared_ptr<entity_type> pObject);
	virtual void Execute(std::shared_ptr<entity_type> pObject, float deltaTime);
	virtual void Exit(std::shared_ptr<entity_type> pObject);
};