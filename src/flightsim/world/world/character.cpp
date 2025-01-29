#include "character.hpp"
#include "item.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <libidk/idk_math.hpp>


idk::Character::Character( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Actor(api, world, p),
    m_head_obj(m_obj),
    m_equipped(nullptr)
{
    for (int i=0; i<8; i++)
    {
        m_inventory.push_back(std::vector<idk::Item*>(5, nullptr));
    }
}


void
idk::Character::update()
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = m_api.dtime();

    // tsys.yaw(m_obj, dt*m_ang.x);
    // tsys.pitch(m_obj, dt*m_ang.y);
    // tsys.roll(m_obj, dt*m_ang.z);

    // m_vel = idk::flerp(m_vel, glm::vec3(0.0f), dt, 0.9f);
    // m_ang = idk::flerp(m_ang, glm::vec3(0.0f), dt, 0.9f);

    m_dlook = idk::flerp(m_dlook, glm::vec3(0.0f), dt, 0.9f);
    m_dmove = idk::flerp(m_dmove, glm::vec3(0.0f), dt, 0.9f);
}


idk::Item*
idk::Character::equippedItem()
{
    return m_equipped;
}


void
idk::Character::equipItem( idk::Item *I )
{
    I->setOwner(this);
    m_equipped = I;
}
