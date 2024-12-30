#include "actor.hpp"
#include "world.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>


sp::Actor::Actor( idk::EngineAPI &api, sp::World &world, const glm::vec3 &p )
:   m_api(api),
    m_world(world),
    m_obj(api.getECS().createGameObject("Actor", false))
{

}


sp::ActorVisible::ActorVisible( idk::EngineAPI &api, sp::World &world, const glm::vec3 &p )
:   Actor(api, world, p)
{
    auto &ecs = api.getECS();
    auto &ren = api.getRenderer();

    // m_obj = ecs.createGameObject("ActorVisible", false);
    idk::ModelSys::assignModel(m_obj, "assets/models/fighter.idkvi");

    // m_nodeid = ren.createNode();
    // idk::Node &node = ren.getNode(m_nodeid);

    // node.model = ren.loadModel("assets/models/fighter.idkvi");
    // node.position = p;
}


void
sp::ActorVisible::update()
{
    auto &ecs = m_api.getECS();
    auto &ren = m_api.getRenderer();

    // idk::TransformSys::getLocalPosition(m_obj) = m_pos;

    // auto &node = ren.getNode(m_nodeid);
    // node.position = m_pos;
}