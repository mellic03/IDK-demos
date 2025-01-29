#include <iostream>

#include <IDKGameEngine/idk_engine_api.hpp>
#include <IDKBuiltinCS/sys-audio.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <libidk/idk_math.hpp>
#include <libidk/idk_random.hpp>

#include <flightsim/world/world/character.hpp>
#include <flightsim/world/weapon/weapon.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    auto &ecs  = api.getECS();
    auto &asys = api.getECS().getSystem<idk::AudioSys>();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = api.dtime();

    if (data == nullptr)
    {
        std::cout << "\ndata == nullptr\n";
        return 0;
    }

    auto *W  = static_cast<idk::Weapon*>(data);
    asys.playSound(W->objID(), false);

    glm::vec3 recoil = W->getConf().recoil;

    float rx = idk::randf(-1, +1) * recoil.x;
    float ry = idk::randf(-1, +1) * recoil.y;
    float rz = idk::randf(0.8, 1.2) *recoil.z;
    W->sway_pos += glm::vec3(rx, ry, rz);

    return 0;
}
