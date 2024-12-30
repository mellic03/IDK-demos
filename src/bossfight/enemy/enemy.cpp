#include "enemy.hpp"
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKBuiltinCS/sys-script.hpp>

using namespace idk;


CharacterEnemy::CharacterEnemy( const glm::vec3 &pos )
:   Actor(pos)
{
    // ECS2::giveComponent<ScriptCmp>(m_obj);

    // ScriptSys::reserve(m_obj, 2);
    // ScriptSys::attachScript(m_obj, 0, "assets/scripts/keyinput.cpp");
    // ScriptSys::attachScript(m_obj, 1, "assets/scripts/mouseinput.cpp");
    // ScriptSys::attachData(m_obj, 0, dynamic_cast<void*>(this));
    // ScriptSys::attachData(m_obj, 1, dynamic_cast<void*>(this));
}


void
CharacterEnemy::move( const glm::vec3 &v )
{
    TransformSys::translateLocalspace(m_obj, v);
}


void
CharacterEnemy::look( const glm::vec2 &v )
{
    TransformSys::yaw(getID(), v.x);
    TransformSys::pitch(getID(), v.y);
}


void
CharacterEnemy::moveTo( const glm::vec3 &poi )
{
    // TransformSys::translateLocalspace(m_obj, v);
}


void
CharacterEnemy::lookTo( const glm::vec3 &poi )
{
    // TransformSys::yaw(getID(), v.x);
    // TransformSys::pitch(getID(), v.y);
}
