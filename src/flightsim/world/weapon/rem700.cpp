#include "weapon.hpp"


idk::WeaponRem700::WeaponRem700( idk::EngineAPI &api, World &world )
:   Weapon(api, world, "Rem 700", "assets/models/rem700.idkvi", "assets/audio/rifle.wav")
{
    m_conf = {
        .rest_pos = glm::vec3(0.02, -0.01, -0.063),
        .rest_rot = glm::vec3(0.0),
        .rest_spd = glm::vec3(0.01),
        .sway_spd = glm::vec3(0.1),
        .aim_pos  = glm::vec3(0.0, -0.0075, -0.025),
        .aim_rot  = glm::vec3(0.0),
        .aim_fov  = 8.0f,
        .cooldown = 1.0/1.0,
        .recoil   = glm::vec3(0.02, 0.02, 0.15f),
        .scale    = 0.2f,
        .model    = "assets/models/rem700.idkvi",
        .audio    = "assets/audio/rifle.wav"
    };
}

