#include "weapon.hpp"


idk::WeaponSten::WeaponSten( idk::EngineAPI &api, World &world )
:   Weapon(api, world, "Sten mk5", "assets/models/sten-mk5.idkvi", "assets/audio/rifle.wav")
{
    m_conf = {
        .rest_pos = glm::vec3(0.02, -0.01, -0.063),
        .rest_rot = glm::vec3(0.055, 0.08, 0.0),
        .rest_spd = glm::vec3(0.05),
        .sway_spd = glm::vec3(1.0),
        .aim_pos  = glm::vec3(0.0, 0.0, -0.06),
        .aim_rot  = glm::vec3(0.0),
        .aim_fov  = 35.0f,
        .cooldown = 1.0/9.16667,
        .recoil   = glm::vec3(0.001, 0.001, 0.02f),
        .scale    = 0.1f,
        .model    = "assets/models/sten-mk5.idkvi",
        .audio    = "assets/audio/glock.wav"
    };
}

