#include <IDKGameEngine/api.hpp>
#include <IDKBuiltinCS/sys-lightsource.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <libidk/idk_math.hpp>

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

    auto *I   = static_cast<idk::WeaponFlashlight*>(data);
    auto &cmp = ecs.getComponent<idk::SpotlightCmp>(I->objID());

    I->intensity = 1.0f;
    cmp.light.angle  = glm::vec3(0.1, 0.25, 0.0);
    cmp.light.radius = 32.0f;

    return 0;
}
