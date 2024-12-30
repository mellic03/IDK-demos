#include "watercraft.hpp"
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKGraphics/terrain/terrain.hpp>

using namespace idk;


demo::WaterCraft::WaterCraft( const glm::vec3 &pos )
:   Actor(pos),
    m_body(ECS2::createGameObject("Body", false)),
    m_seat(ECS2::createGameObject("Seat", false)),
    m_vel(0.0f)
{
    ECS2::setGameObjectName(m_obj, "WaterCraft");

    ECS2::giveChild(m_obj, m_body);
    ECS2::giveChild(m_body, m_seat);

    TransformSys::getLocalPosition(m_body) = glm::vec3(0.0f);
    TransformSys::getLocalPosition(m_seat) = glm::vec3(0.0f, 6.8f, -9.8f);

    ModelSys::assignModel(m_body, "assets/models/ship-pinnacle.idkvi");

    ECS2::giveComponent<ScriptCmp>(m_obj);
    ScriptSys::reserve(m_obj, 1);
    ScriptSys::attachScript(m_obj, 0, "watercraft");
    ScriptSys::attachData(m_obj, 0, dynamic_cast<void*>(this));
}


void
demo::WaterCraft::update( idk::EngineAPI &api )
{
    float dt = api.dtime();

    TransformSys::getLocalPosition(m_obj) += m_vel;

    float a = glm::clamp((32.0f*dt), 0.0f, 1.0f);
    m_vel = glm::mix(m_vel, glm::vec3(0.0f), a);

}


