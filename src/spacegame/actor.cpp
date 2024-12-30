#include "actor.hpp"
#include "world.hpp"
#include <IDKGameEngine/IDKGameEngine.hpp>
// #include <IDKGraphics/idk_rendernode.hpp>


sp::Actor::Actor( idk::EngineAPI &api, sp::World &world, const glm::vec3 &p )
:   m_api(api),
    m_world(world),
    pos(p)
{

}

sp::ActorVisible::ActorVisible( idk::EngineAPI &api, sp::World &world, const glm::vec3 &p )
:   Actor(api, world, p)
{
    // m_rendernode = new idk::RenderNode(-1, p);
}
