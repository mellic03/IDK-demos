#include "weapon.hpp"

#include <IDKBuiltinCS/sys-audio.hpp>
#include <IDKBuiltinCS/sys-lightsource.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>


idk::WeaponFlashlight::WeaponFlashlight( idk::EngineAPI &api, World &world )
:   Weapon(api, world, "FlashLight", "", "assets/audio/click.wav")
{
    m_conf = {
        .rest_pos = glm::vec3(0.0),
        .rest_rot = glm::vec3(0.0),
        .rest_spd = glm::vec3(0.1),
        .sway_spd = glm::vec3(2.0),

        .aim_pos  = glm::vec3(0.0),
        .aim_rot  = glm::vec3(0.0),
        .aim_fov  = 15.0f,

        .recoil   = glm::vec3(0.0)
    };

    auto &ecs = api.getECS();
    auto &asys = ecs.getSystem<idk::AudioSys>();
    auto &ssys = ecs.getSystem<idk::ScriptSys>();

    ssys.attachScript(m_obj, "assets/scripts/flashlight-config", dynamic_cast<void*>(this));

    ecs.giveComponent<idk::SpotlightCmp>(m_obj);
    auto &cmp = ecs.getComponent<idk::SpotlightCmp>(m_obj);
    cmp.light.radius = 32.0f;
    cmp.light.angle  = glm::vec3(0.5f, 0.65f, 1.0f);

    this->fire();
}



void
idk::WeaponFlashlight::fire()
{
    auto &ecs  = m_api.getECS();
    auto &asys = ecs.getSystem<idk::AudioSys>();
    auto &cmp  = ecs.getComponent<idk::SpotlightCmp>(m_obj);

    cmp.light.diffuse = glm::vec4(0.0f);

    if (m_on)
    {
        cmp.light.diffuse = intensity * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    m_on = !m_on;
    asys.playSound(m_obj, false);
}

