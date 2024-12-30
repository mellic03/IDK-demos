#include "rigidbody.hpp"
#include "physicsworld.hpp"
#include "../util.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>



fsim::RigidBody::RigidBody( fsim::PhysicsWorld &world, const glm::vec3 &position )
:   m_world  (world),
    m_local  (glm::vec3(0.0f), glm::quat(glm::vec3(0.0f))),
    m_curr   (position, glm::quat(glm::vec3(0.0f))),
    m_prev   (m_curr),
    m_lerp   (m_curr),
    m_vel    (0.0f),
    m_ang    (0.0f),
    m_force  (0.0f),
    m_torque (0.0f),
    m_scale  (1.0f),
    m_mass   (1.0f)
{
    setScale(glm::vec3(1.0f));
}


void
fsim::RigidBody::setScale( const glm::vec3 &scale )
{
    m_scale       = scale;
    m_inertia     = fsim::util::computeInertiaTensor(m_mass, m_scale, m_curr.rot);
    m_inv_inertia = glm::inverse(m_inertia);
}



glm::mat4
fsim::RigidBody::getTransform()
{
    glm::mat4 T = glm::translate(glm::mat4(1.0f), m_lerp.pos);
    glm::mat4 R = glm::mat4_cast(m_lerp.rot);
    glm::mat4 S = glm::scale(glm::mat4(1.0f), m_scale);
    return T*R*S;
}



void
fsim::RigidBody::interpolateState( float alpha )
{
    m_lerp.pos = glm::mix(m_prev.pos, m_curr.pos, alpha);
    m_lerp.rot = glm::slerp(m_prev.rot, m_curr.rot, alpha);
}



glm::vec3
fsim::RigidBody::computeLinearDrag()
{
    // auto  T    = getTransform();
    // auto  down = -glm::normalize(glm::mat3(T) * glm::vec3(0.001, 1.0,  0.001));

    // float Cd  = 0.5f;
    // float rho = 1.225f; // Air density (kg/m^3)
    float Cd  = m_world.config.linearDrag;
    float rho = m_world.config.airDensity;
    float A   = 1.0f;   // Cross-sectional area (m^2)

    float magSq = glm::length2(m_vel);

    if (magSq > 0.0f)
    {
        glm::vec3 drag_dir   = -glm::normalize(m_vel);
        glm::vec3 drag_force = 0.5f * Cd * rho * A * magSq * drag_dir;
        return drag_force / m_mass;
    }

    return glm::vec3(0.0f);
}


glm::vec3
fsim::RigidBody::computeAngularDrag()
{
    float Cd = m_world.config.angularDrag;
    glm::vec3 drag_torque = -Cd * m_ang;
    return drag_torque;
}



void
fsim::RigidBody::integrate()
{
    if (this->auto_integrate == false)
    {
        return;
    }

    m_prev = m_curr;

    float dt  = m_world.config.timestep;
    auto  acc = m_force / m_mass;

    if (has_gravity)
    {
        acc += m_world.config.gravity;
    }

    acc += computeLinearDrag();
    m_torque += computeAngularDrag();

    m_vel      += acc * dt;
    m_curr.pos += m_vel * dt;
    m_ang      += m_inv_inertia * (m_torque - glm::cross(m_ang, m_inertia * m_ang)) * dt;
    m_curr.rot += (m_curr.rot * glm::quat(0.0f, m_ang)) * (0.5f * dt);
    m_curr.rot  = glm::normalize(m_curr.rot);

    m_force  = glm::vec3(0.0f);
    m_torque = glm::vec3(0.0f);
}


void
fsim::RigidBody::render( idk::EngineAPI &api )
{
    auto &ren   = api.getRenderer();
    auto  T     = getTransform();
    auto  front = glm::mat3(T) * glm::vec3(0.01, 0.01, -1.0);
    auto  down  = -glm::normalize(glm::mat3(T) * glm::vec3(0.001, 1.0,  0.001));

    ren.drawRect(T, m_prev_T);
    ren.drawCapsule(m_lerp.pos, m_lerp.pos+4.0f*down, 0.2f);

    m_prev_T = T;
}

