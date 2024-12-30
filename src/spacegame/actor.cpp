#include "actor.hpp"
#include "world.hpp"
#include <IDKGameEngine/IDKGameEngine.hpp>


sp::Actor::Actor( idk::EngineAPI &api, sp::World &world, const glm::vec3 &p )
:   m_api(api),
    m_world(world),
    m_pos(p),
    pos(m_pos)
{

}


sp::ActorVisible::ActorVisible( idk::EngineAPI &api, sp::World &world, const glm::vec3 &p )
:   Actor(api, world, p)
{
    auto &ren = api.getRenderer();
    m_nodeid = ren.createNode();

    idk::Node &node = ren.getNode(m_nodeid);

    node.model = ren.loadModel("assets/models/fighter.idkvi");
    node.position = p;
}


void
sp::ActorVisible::update()
{
    auto &ren  = m_api.getRenderer();
    auto &node = ren.getNode(m_nodeid);

    node.position = m_pos;

}