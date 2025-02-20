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
    float dt = m_api.dtime();

    m_ctl.dmove = idk::flerp(m_ctl.dmove, glm::vec3(0.0f), dt, m_ctl.move_decay);
    m_ctl.dlook = idk::flerp(m_ctl.dlook, glm::vec3(0.0f), dt, m_ctl.look_decay);

    this->move(m_ctl.dmove);
    this->look(m_ctl.dlook);
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
