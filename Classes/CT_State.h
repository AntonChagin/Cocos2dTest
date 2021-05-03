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

template<class entity_type>
inline CT_State<entity_type>::~CT_State()
{
}

template<class entity_type>
inline void CT_State<entity_type>::Enter(std::shared_ptr<entity_type> pObject)
{
}

template<class entity_type>
inline void CT_State<entity_type>::Execute(std::shared_ptr<entity_type> pObject, float deltaTime)
{
}

template<class entity_type>
inline void CT_State<entity_type>::Exit(std::shared_ptr<entity_type> pObject)
{
}
