#include "compositebody.hpp"
#include "physicsworld.hpp"
#include "../util.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>



fsim::RigidBodyComposite::RigidBodyComposite( fsim::PhysicsWorld &world, const glm::vec3 &pos )
:   RigidBody(world, pos)
{

}


float
fsim::RigidBodyComposite::computeCompositeMass()
{
    float totalMass = 0.0f;

    for (auto *body: m_components)
    {
        totalMass += body->m_mass;
    }

    return totalMass;
}


glm::vec3
fsim::RigidBodyComposite::computeCenterOfMass( float totalMass )
{
    auto COM = glm::vec3(0.0f);

    for (auto *body: m_components)
    {
        COM += body->m_mass * body->m_local.pos;
    }

    return COM / totalMass;
}


glm::vec3
fsim::RigidBodyComposite::computeCompositeForce( float totalMass )
{
    auto totalForce = glm::vec3(0.0f);

    for (auto *body: m_components)
    {
        glm::vec3 force = body->m_force;
    
        if (body->has_gravity)
        {
            force += m_world.config.gravity;
        }

        totalForce += body->m_mass * force;
    }

    return totalForce / totalMass;

}


glm::vec3
fsim::RigidBodyComposite::computeCompositeTorque( float totalMass )
{
    auto totalTorque = glm::vec3(0.0f);

    for (auto *body: m_components)
    {
        totalTorque += body->getMass() * body->getTorque();
    }

    return totalTorque / totalMass;
}


glm::mat3
fsim::RigidBodyComposite::computeCompositeInertia( const glm::vec3 &COM )
{
    glm::mat3 result = glm::mat3(0.0f);

    for (auto *body: m_components)
    {
        glm::vec3 r        = body->getLocalPosition() - COM;
        float     distSq   = glm::dot(r, r);
        glm::mat3 outer    = glm::outerProduct(r, r);
        glm::mat3 parallel = body->getMass() * (distSq * glm::mat3(1.0f) - outer);

        result += body->getLocalInertiaTensor() + parallel;
    }

    return result;
}


glm::vec3
fsim::RigidBodyComposite::computeLinearDrag()
{
    glm::vec3 result = glm::vec3(0.0f);

    for (auto *body: m_components)
    {
        result += body->computeLinearDrag();
    }

    return result;
}


glm::vec3
fsim::RigidBodyComposite::computeAngularDrag()
{
    glm::vec3 result = glm::vec3(0.0f);

    for (auto *body: m_components)
    {
        result += body->computeAngularDrag();
    }

    return result;
}





void
fsim::RigidBodyComposite::integrate()
{
    m_prev = m_curr;

    float     dt     = m_world.config.timestep;
    float     m_mass = computeCompositeMass();
    glm::vec3 COM    = computeCenterOfMass(m_mass);
    glm::vec3 acc    = computeCompositeForce(m_mass);

    m_torque      = computeCompositeTorque(m_mass);
    m_inertia     = computeCompositeInertia(COM);
    m_inv_inertia = glm::inverse(m_inertia);

    acc        += computeLinearDrag();
    m_torque   += computeAngularDrag();

    m_vel      += acc * dt;
    m_curr.pos += m_vel * dt;
    m_ang      += m_inv_inertia * (m_torque - glm::cross(m_ang, m_inertia * m_ang)) * dt;
    m_curr.rot += (m_curr.rot * glm::quat(0.0f, m_ang)) * (0.5f * dt);
    m_curr.rot  = glm::normalize(m_curr.rot);


    glm::mat4 M0 = getTransform();

    for (auto *body: m_components)
    {
        body->m_prev = body->m_curr;

        glm::mat4 T = glm::translate(glm::mat4(1.0f), body->m_local.pos);
        glm::mat4 R = glm::mat4_cast(glm::normalize(body->m_local.rot));
        glm::mat4 M1 = M0*T*R;

        body->m_curr.pos = glm::vec3(M1 * glm::vec4(body->m_local.pos, 1.0f));
        body->m_curr.rot = glm::normalize(glm::quat_cast(glm::mat3(M1)));

        body->m_force  *= 0.0f;
        body->m_torque *= 0.0f;
    }
}


void
fsim::RigidBodyComposite::render( idk::EngineAPI &api )
{
    RigidBody::render(api);

    for (auto *body: m_components)
    {
        body->render(api);
    }
}

