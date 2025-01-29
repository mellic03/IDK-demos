#include "vehicle.hpp"
#include "world.hpp"

#include <IDKECS/IDKECS.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKGraphics/terrain/terrain.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <libidk/idk_math.hpp>
#include <print>

idk::Vehicle::Vehicle( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Actor(api, world, p)
{
    auto &ecs = api.getECS();
    auto &ren = api.getRenderer();
    auto &msys = ecs.getSystem<idk::ModelSys>();

    ecs.setGameObjectName(m_obj, "Vehicle");
    // msys.assignModel(m_obj, "assets/models/helicopter.idkvi");
}

// void
// idk::Vehicle::look( const glm::vec3 &delta )
// {

// }


// void
// idk::Vehicle::move( const glm::vec3 &delta )
// {
//     auto &ecs = m_api.getECS();
//     auto &tsys = ecs.getSystem<idk::TransformSys>();

//     tsys.moveRight(m_obj, delta.x);
//     tsys.moveUp(m_obj, delta.y);
//     tsys.moveFront(m_obj, delta.z);
// }


void
idk::Vehicle::drive( idk::Character *A )
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();

    ecs.giveChild(m_obj, A->objID());
    tsys.getTransformCmp(A->objID()).yaw = M_PI;
    tsys.getLocalPosition(A->objID()) = m_seatpos;

    driver = A;
    A->vehicle = this;
}


void
idk::Vehicle::undrive()
{
    auto &ecs  = m_api.getECS();
    ecs.removeChild(m_obj, driver->objID());

    driver->vehicle = nullptr;
    driver = nullptr;
}


