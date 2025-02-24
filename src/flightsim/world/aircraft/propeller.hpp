#pragma once
#include <IDKPhysics/IDKPhysics.hpp>

namespace idk
{
    class Propeller;
}


class idk::Propeller
{
protected:
    idk::phys::World &m_world;
    int m_segments;

public:
    glm::mat4 transform = glm::mat4(1.0f);

    // Propeller( idk::phys::World &world, const glm::vec3 &base, const glm::vec3 &end, int segments=8 );

    // glm::vec3 computeAeroForces( const glm::mat4 &parent );
    // glm::mat4 getRenderMatrix( const glm::mat4 &parent );
};
