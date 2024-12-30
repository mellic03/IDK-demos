#include "player.hpp"
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKBuiltinCS/sys-script.hpp>

using namespace idk;


demo::Player::Player( const glm::vec3 &pos )
:   idk::Freecam(pos)
{
    ECS2::setGameObjectName(m_obj, "Player");
    // ScriptSys::reserve(m_obj, 2);
    // ScriptSys::attachScript(m_obj, 0, "assets/scripts/keyinput.cpp");
    // ScriptSys::attachScript(m_obj, 1, "assets/scripts/mouseinput.cpp");
    ScriptSys::attachData(m_obj, 0, dynamic_cast<void*>(this));
    ScriptSys::attachData(m_obj, 1, dynamic_cast<void*>(this));
}


void
demo::Player::move( const glm::vec3 &v )
{
    TransformSys::translateLocalspace(m_obj, v);
}


void
demo::Player::look( const glm::vec2 &v )
{
    TransformSys::yaw(getID(), v.x);
    TransformSys::pitch(getID(), v.y);
}
