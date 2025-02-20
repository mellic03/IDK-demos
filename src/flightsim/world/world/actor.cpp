#include "actor.hpp"
#include "world.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKGraphics/IDKGraphics.hpp>
#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <libidk/idk_math.hpp>


idk::Actor::Actor( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   m_api(api),
    m_world(world),
    m_obj(api.getECS().createGameObject("Actor", false))
{
    api.getECS().getSystem<idk::TransformSys>().getLocalPosition(m_obj) = p;
}


idk::Actor::~Actor()
{
    m_api.getECS().deleteGameObject(m_obj, true);
}


void
idk::Actor::update()
{

}


void
idk::Actor::fixedUpdate( float timestep )
{

}


void
idk::Actor::render( idk::RenderEngine &ren )
{

}




glm::vec3
idk::Actor::getLocalPosition() const
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    return tsys.getLocalPosition(m_obj);
}


glm::vec3
idk::Actor::getWorldPosition() const
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    return tsys.getWorldPosition(m_obj);
}

glm::vec3
idk::Actor::getFront() const
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    return tsys.getFront(m_obj);
}
