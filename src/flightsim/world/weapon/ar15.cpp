#include "weapon.hpp"


idk::WeaponAR15::WeaponAR15( idk::EngineAPI &api, World &world )
:   Weapon(api, world, "AR15", "assets/models/AR.idkvi", "assets/audio/rifle.wav")
{
    m_conf = {
        .rest_pos = glm::vec3(0.09, -0.08, -0.17),
        .rest_rot = glm::vec3(0.0),
        .rest_spd = glm::vec3(0.1),
        .sway_spd = glm::vec3(2.0),
        .aim_pos  = glm::vec3(0.01, -0.06, -0.1),
        .aim_rot  = glm::vec3(0.0, 0.0, -1.025),
        .aim_fov  = 55.0f,
        .cooldown = 1.0/4.0,
        .recoil   = glm::vec3(0.02, 0.02, 0.25f),
        .scale    = 0.1f,
        .model    = "assets/models/AR.idkvi",
        .audio    = "assets/audio/rifle.wav"
    };
}

