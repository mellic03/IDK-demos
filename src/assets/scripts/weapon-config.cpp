#include <iostream>

#include <IDKGameEngine/idk_engine_api.hpp>
#include <flightsim/world/weapon/weapon.hpp>



extern "C"
int script( idk::EngineAPI &api, void *data )
{
    // idk::WeaponAR15::conf = {
    //     .rest_pos = glm::vec3(0.09, -0.08, -0.17),
    //     .rest_rot = glm::vec3(0.0),
    //     .rest_spd = glm::vec3(0.1),
    //     .sway_spd = glm::vec3(2.0),
    //     .aim_pos  = glm::vec3(0.01, -0.06, -0.1),
    //     .aim_rot  = glm::vec3(0.0, 0.0, -1.025),
    //     .aim_fov  = 55.0f,
    //     .cooldown = 1.0/4.0,
    //     .recoil   = glm::vec3(0.02, 0.02, 0.25f),
    //     .scale    = 0.1f,
    //     .model    = "assets/models/AR.idkvi",
    //     .audio    = "assets/audio/rifle.wav"
    // };

    // idk::WeaponAK47::conf = {
    //     .rest_pos = glm::vec3(0.1, -0.12, -0.25),
    //     .rest_rot = glm::vec3(0.055, 0.08, 0.0),
    //     .rest_spd = glm::vec3(0.1),
    //     .sway_spd = glm::vec3(2.0),
    //     .aim_pos  = glm::vec3(0.0, -0.09, -0.08),
    //     .aim_rot  = glm::vec3(0.01, 0.0, 0.0),
    //     .aim_fov  = 25.0f,
    //     .cooldown = 1.0/10.0,
    //     .recoil   = glm::vec3(0.002, 0.002, 0.05f),
    //     .scale    = 0.1f,
    //     .model    = "assets/models/ak47.idkvi",
    //     .audio    = "assets/audio/rifle.wav"
    // };

    // idk::WeaponSten::conf = {
    //     .rest_pos = glm::vec3(0.02, -0.01, -0.063),
    //     .rest_rot = glm::vec3(0.055, 0.08, 0.0),
    //     .rest_spd = glm::vec3(0.05),
    //     .sway_spd = glm::vec3(1.0),
    //     .aim_pos  = glm::vec3(0.0, 0.0, -0.06),
    //     .aim_rot  = glm::vec3(0.0),
    //     .aim_fov  = 35.0f,
    //     .cooldown = 1.0/9.16667,
    //     .recoil   = glm::vec3(0.001, 0.001, 0.02f),
    //     .scale    = 0.1f,
    //     .model    = "assets/models/sten-mk5.idkvi",
    //     .audio    = "assets/audio/glock.wav"
    // };

    // idk::WeaponRem700::conf = {
    //     .rest_pos = glm::vec3(0.02, -0.01, -0.063),
    //     .rest_rot = glm::vec3(0.0),
    //     .rest_spd = glm::vec3(0.01),
    //     .sway_spd = glm::vec3(0.1),
    //     .aim_pos  = glm::vec3(0.0, -0.0075, -0.025),
    //     .aim_rot  = glm::vec3(0.0),
    //     .aim_fov  = 8.0f,
    //     .cooldown = 1.0/1.0,
    //     .recoil   = glm::vec3(0.02, 0.02, 0.15f),
    //     .scale    = 0.2f,
    //     .model    = "assets/models/rem700.idkvi",
    //     .audio    = "assets/audio/rifle.wav"
    // };

    return 0;
}
