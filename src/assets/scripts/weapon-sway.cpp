#include <iostream>

#include <IDKGameEngine/idk_engine_api.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <libidk/idk_math.hpp>

#include <flightsim/world/world/character.hpp>
#include <flightsim/world/weapon/weapon.hpp>




extern "C"
int script( idk::EngineAPI &api, void *data )
{
    auto &ecs  = api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = api.dtime();

    if (data == nullptr)
    {
        std::cout << "\ndata == nullptr\n";
        return 0;
    }

    auto *W  = static_cast<idk::Weapon*>(data);
    auto *C  = W->getOwner();
    int  obj = W->objID();

    auto &conf       = W->getConf();
    auto  rest_pos   = conf.rest_pos;
    auto  rest_spd   = conf.rest_spd;
    auto  rest_rot   = conf.rest_rot;

    auto  aim_rot    = conf.aim_rot;
    auto  aim_pos    = conf.aim_pos;

    auto &sway_pos   = W->sway_pos;
    auto  sway_spd   = conf.sway_spd;

    auto &curr_pos   = W->curr_pos;
    auto &curr_rot   = W->curr_rot;

    glm::vec3 target_pos;
    glm::vec3 target_rot;

    if (W->isAiming())
    {
        target_pos = aim_pos;
        curr_rot   = aim_rot;
        sway_spd   = glm::vec3(0.05f);
        rest_spd   = glm::vec3(0.0025f);
        tsys.getTransformCmp(obj).pitch = aim_rot.x;
        tsys.getTransformCmp(obj).yaw   = aim_rot.y;
        tsys.getTransformCmp(obj).roll  = aim_rot.z;
    }

    else
    {
        target_pos = rest_pos;
        curr_rot   = rest_rot;
        tsys.getTransformCmp(obj).pitch = rest_rot.x;
        tsys.getTransformCmp(obj).yaw   = rest_rot.y;
        tsys.getTransformCmp(obj).roll  = rest_rot.z;
    }

    glm::vec3 dlook = W->getOwner()->dlook();
    glm::vec3 dmove = W->getOwner()->dmove();

    sway_pos += dt * dlook * sway_spd * glm::vec3(1, -1, 0);

    for (int i=0; i<3; i++)
    {
        sway_pos[i] = idk::flerp(sway_pos[i], 0.0f, dt, 0.25f);
        curr_pos[i] = idk::flerp(curr_pos[i], target_pos[i], dt, 0.25f);
        curr_rot[i] = idk::flerp(curr_rot[i], target_rot[i], dt, 0.25f);
    }

    tsys.getLocalPosition(obj) = curr_pos + sway_pos;

    return 0;
}
