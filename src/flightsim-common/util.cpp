#include "util.hpp"

glm::mat3
fsim::util::computeInertiaTensor( float mass, const glm::vec3 &scale, const glm::quat &rot )
{
    float w = scale.x;
    float h = scale.y;
    float d = scale.z;

    float ixx = (mass / 12.0f) * (h*h + d*d);
    float iyy = (mass / 12.0f) * (w*w + d*d);
    float izz = (mass / 12.0f) * (w*w + h*h);

    glm::mat3 inertia = glm::mat3(
        ixx,  0.0f, 0.0f,
        0.0f, iyy,  0.0f,
        0.0f, 0.0f, izz
    );

    glm::mat3 R = glm::mat3_cast(rot);

    return inertia;
}


glm::mat3
fsim::util::computeInertiaTensorCOG( float mass, const glm::vec3 &offset, const glm::mat3 &inertia )
{
    float d2 = glm::dot(offset, offset);
    glm::mat3 I = glm::mat3(1.0f);
    glm::mat3 offsetOuterProduct = glm::outerProduct(offset, offset);
    return inertia + mass * (d2 * glm::mat3(1.0f) - offsetOuterProduct);
}


