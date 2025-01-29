#include "weapon.hpp"


idk::WeaponHands::WeaponHands( idk::EngineAPI &api, World &world )
:   Weapon(api, world, "Hands", "", "assets/audio/click.wav")
{
    m_conf = {
        .rest_pos = glm::vec3(0.1, -0.12, -0.25),
        .rest_rot = glm::vec3(0.055, 0.08, 0.0),
        .rest_spd = glm::vec3(0.1),
        .sway_spd = glm::vec3(2.0),
        .aim_pos  = glm::vec3(0.0, -0.09, -0.08),
        .aim_rot  = glm::vec3(0.01, 0.0, 0.0),
        .aim_fov  = 25.0f,
        .cooldown = 1.0/10.0,
        .recoil   = glm::vec3(0.002, 0.002, 0.05f),
        .scale    = 0.1f,
        .model    = "",
        .audio    = "assets/audio/click.wav"
    };
}

