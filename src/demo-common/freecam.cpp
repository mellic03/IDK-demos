#include "freecam.hpp"
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKBuiltinCS/sys-script.hpp>

using namespace idk;


Freecam::Freecam( const glm::vec3 &pos, bool drag )
:   Actor(pos),
    m_cam_obj(ECS2::createGameObject("Camera", false))
{
    ECS2::setGameObjectName(m_obj, "Freecam");

    ECS2::giveComponent<ScriptCmp>(m_obj);
    ScriptSys::reserve(m_obj, 2);
    ScriptSys::attachScript(m_obj, 0, "keyinput");

    if (drag == true)
    {
        ScriptSys::attachScript(m_obj, 1, "freecam-drag");
    }

    else
    {
        ScriptSys::attachScript(m_obj, 1, "freecam-look");
    }

    ScriptSys::attachData(m_obj, 0, dynamic_cast<void*>(this));
    ScriptSys::attachData(m_obj, 1, dynamic_cast<void*>(this));

    ECS2::giveChild(m_obj, m_cam_obj);
    ECS2::giveComponent<CameraCmp>(m_cam_obj);
    TransformSys::getLocalPosition(m_cam_obj) *= 0.0f;
}


void
Freecam::move( const glm::vec3 &v )
{
    TransformSys::translateLocalspace(m_obj, v);
}


void
Freecam::look( const glm::vec2 &v )
{
    TransformSys::yaw(getID(), v.x);
    TransformSys::pitch(getID(), v.y);
}
