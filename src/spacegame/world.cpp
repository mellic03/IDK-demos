#include "world.hpp"


void
sp::World::update()
{
    for (sp::Actor *A: m_actors)
    {
        A->update();
    }
}
