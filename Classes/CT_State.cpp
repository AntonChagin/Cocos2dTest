#include "CT_State.h"
#include <CT_Player.h>

template<class entity_type>
 CT_State<entity_type>::~CT_State()
{
}

template<class entity_type>
 void CT_State<entity_type>::Enter(std::shared_ptr<entity_type> pObject)
{
}

template<class entity_type>
 void CT_State<entity_type>::Execute(std::shared_ptr<entity_type> pObject, float deltaTime)
{
}

template<class entity_type>
 void CT_State<entity_type>::Exit(std::shared_ptr<entity_type> pObject)
{
}

template CT_State<CT_Player>;