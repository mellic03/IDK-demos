#include "joint.hpp"
#include "rigidbody.hpp"
#include "../util.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>


fsim::GlueJoint::GlueJoint( RigidBody *A, RigidBody *B, const glm::vec3 &offset )
:   bodyA(A), bodyB(B)
{
    bodyB->m_local.pos = offset;
}


void
fsim::GlueJoint::update()
{
    // glm::mat4 T = bodyA->getTransform();

    // glm::vec3 pos_local = bodyB->m_local.pos;
    // glm::quat rot_local = bodyB->m_local.rot;

    // bodyB->m_curr.pos = glm::vec3(T * glm::vec4(pos_local, 1.0f));
    // bodyB->m_curr.rot = glm::quat_cast(T * glm::mat4_cast(rot_local));
    // bodyB->m_curr.rot = glm::normalize(bodyB->m_curr.rot);
}


void
fsim::GlueJoint::integrate()
{
    // bodyB->m_prev = bodyB->m_curr;

    // float dt  = bodyB->m_world.config.timestep;

    // auto acc     = bodyB->m_force / bodyB->m_mass;
    // auto &vel    = bodyB->m_vel;
    // auto &pos    = bodyB->m_curr.pos;
    // auto &rot    = bodyB->m_curr.rot;
    // auto &ang    = bodyB->m_ang;
    // auto &torque = bodyB->m_torque;

    // acc += bodyB->computeLinearDrag();
    // bodyB->m_torque += bodyB->computeAngularDrag();


    // vel += acc * dt;
    // pos += vel * dt;
    // ang += bodyB->m_inv_inertia * (torque - glm::cross(ang, bodyB->m_inertia * ang)) * dt;
    // rot += (rot * glm::quat(0.0f, ang)) * (0.5f * dt);
    // rot  = glm::normalize(rot);


    // bodyB->m_force  = glm::vec3(0.0f);
    // bodyB->m_torque = glm::vec3(0.0f);

    // bodyB->getPosition() = bodyA->getPosition() + offset;
    // bodyB->getRotation() = bodyA->getRotation();
}


