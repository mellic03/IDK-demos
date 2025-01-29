#include "creature.hpp"
#include <libidk/idk_random.hpp>
#include <IDKGraphics/IDKGraphics.hpp>


evo::Creature::Creature( const glm::vec3 &p )
:   m_pos(p)
{
    
}


void
evo::Creature::update()
{
    m_root->world = m_root->local;
    m_root->update();

    if (0)
    {
        reproduce();
    }
}


void
evo::Creature::render( idk::RenderEngine &ren )
{
    m_root->render(ren);
}


evo::Creature
evo::Creature::reproduce()
{
    Creature child(m_pos + idk::randvec3(-2.0f, +2.0f));

    child.m_mutation_rate = m_mutation_rate;
    child.m_root = m_root->copy(m_mutation_rate);

    return child;
}

