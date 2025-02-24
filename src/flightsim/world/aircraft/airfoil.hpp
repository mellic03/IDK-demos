#pragma once
#include <IDKPhysics/IDKPhysics.hpp>

namespace idk
{
    class Airfoil;
}


class idk::Airfoil
{
protected:
    idk::phys::World &m_world;

    float m_span;
    float m_chord;
    float m_area;
    float m_aspect_ratio;
    float m_flap_ratio;
    float m_min_aoa;
    float m_max_aoa;
    std::vector<glm::vec3> m_data;
    std::pair<float, float> _sampleLiftDragCoefficients( float aoa );

public:
    glm::vec3 localpos = glm::vec3(0.0f);
    glm::vec3 worldpos = glm::vec3(0.0f);
    glm::vec3 prevpos  = glm::vec3(0.0f);
    glm::mat4 transform = glm::mat4(1.0f);
    float wingAngle = 0.0f;

    Airfoil( idk::phys::World &world, float span=3.8f, float chord=1.26f );

    glm::vec3 computeAeroForcesLinear( const glm::mat4 &parent, const glm::vec3 &pvel );
    glm::mat4 getRenderMatrix( const glm::mat4 &parent );
};
