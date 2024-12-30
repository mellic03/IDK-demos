#include "actor.hpp"
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKBuiltinCS/sys-script.hpp>

using namespace idk;


Actor::Actor( const glm::vec3 &pos )
:   m_obj(ECS2::createGameObject("Actor", false))
{
    TransformSys::getLocalPosition(m_obj) = pos;
}


void
Actor::move( const glm::vec3 &v )
{
    TransformSys::translateLocalspace(m_obj, v);
}


void
Actor::look( const glm::vec2 &v )
{
    TransformSys::yaw(getID(), v.x);
    TransformSys::pitch(getID(), v.y);
}
