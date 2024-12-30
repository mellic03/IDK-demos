#pragma once

#ifndef GLM_ENABLE_EXPERIMENTAL
    #define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>



namespace fsim::util
{
    glm::mat3 computeInertiaTensor( float mass, const glm::vec3 &scale, const glm::quat &rot );
    glm::mat3 computeInertiaTensorCOG( float mass, const glm::vec3 &offset, const glm::mat3 &inertia );
}


