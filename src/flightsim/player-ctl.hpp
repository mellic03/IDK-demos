#pragma once
#include <glm/glm.hpp>

namespace evo
{
    struct PlayerCtl;
}


struct evo::PlayerCtl
{
    glm::vec3 dmove       = glm::vec3(0.0f);
    glm::vec3 dlook       = glm::vec3(0.0f);
    bool      aim         = false;
    float     rest_fov    = 90.0f;
    float     zoom_fov    = 30.0f;
    float     zoom_factor = 0.0f;
    int       equip_idx   = 0;
};
