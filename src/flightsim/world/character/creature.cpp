#include "creature.hpp"
#include <libidk/idk_random.hpp>
#include <IDKGameEngine/idk_engine_api.hpp>
#include <IDKGraphics/IDKGraphics.hpp>
#include <IDKECS/IDKECS.hpp>


idk::Creature::Creature( idk::EngineAPI &api, World &world, const glm::vec3 &p )
:   Character(api, world, p)
{
    api.getECS().setGameObjectName(m_obj, "Creature");
    m_root = new idk::BodyPartStructural();
    m_root->addChild(new idk::BodyPartLeg(glm::vec3(-1, 0, 0)));
    m_root->addChild(new idk::BodyPartLeg(glm::vec3(+1, 0, 0)));
}


void
idk::Creature::update()
{
    m_root->m_local = glm::translate(glm::mat4(1), getWorldPosition());
    m_root->update();

    if (0)
    {
        reproduce();
    }
}


void
idk::Creature::render( idk::RenderEngine &ren )
{
    m_root->render(ren);
}


idk::Creature
idk::Creature::reproduce()
{
    glm::vec3 pos  = this->getWorldPosition();
    glm::vec3 cpos = pos + idk::randvec3(-2.0f, +2.0f);

    Creature child(m_api, m_world, cpos);

    child.m_mutation_rate = m_mutation_rate;
    child.m_root = m_root->copy(m_mutation_rate);

    return child;
}

