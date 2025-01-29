#include "item.hpp"
#include "world.hpp"
#include "character.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <libidk/idk_math.hpp>
#include <libidk/idk_print.hpp>


idk::Item::Item( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   m_api(api),
    m_world(world),
    m_owner(nullptr)
{
    auto &ecs  = api.getECS();
    auto &tsys = ecs.getSystem<TransformSys>();

    m_obj = ecs.createGameObject("Item", false);
    tsys.getLocalPosition(m_obj) = p;
}


idk::Item::~Item()
{
    m_api.getECS().deleteGameObject(m_obj, true);
}
