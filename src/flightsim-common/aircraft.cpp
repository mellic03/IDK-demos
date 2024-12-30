#include "physics/physicsworld.hpp"
#include "physics/rigidbody.hpp"

#include "aircraft.hpp"
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKIO/IDKIO.hpp>

#include <libidk/idk_math.hpp>





fsim::ControlSurface::ControlSurface( fsim::PhysicsWorld &world, const glm::vec3 &pos )
:   RigidBodyComposite(world, pos)
{
    m_body    = pushComponent<RigidBody>(glm::vec3(0.0,  0.0,  0.0),  glm::vec3(8.0,  0.125,  4.0));
    m_aileron = pushComponent<RigidBody>(glm::vec3(0.0,  0.0,  1.5),  glm::vec3(8.0,  0.125,  2.0));
}


glm::vec3
fsim::ControlSurface::computeLinearDrag()
{
    auto  T  = m_aileron->getTransform();
    auto  up = glm::normalize(glm::mat3(T) * glm::vec3(0.001, 1.0,  0.001));

    float Cd  = m_world.config.linearDrag;
    float rho = m_world.config.airDensity;
    float A   = 0.5f;   // Cross-sectional area (m^2)

    float magSq = glm::length2(m_vel);

    if (magSq > 0.01f)
    {
        return magSq * A * up;
    }
    
    return glm::vec3(0.0f);
}


glm::vec3
fsim::ControlSurface::computeAngularDrag()
{
    glm::vec3 vel = m_vel;

    if (glm::length2(m_vel) > 0.0f)
    {
        glm::mat4 T   = m_aileron->getTransform();
        glm::vec3 dir = -glm::normalize(m_vel);
        glm::vec3 up  = glm::normalize(glm::mat3(T) * glm::vec3(0.001, 1.0,  0.001));

        float area     = 8.0f * 2.0f;
        float strength = area * glm::max(glm::dot(dir, up), 0.0f);
        float Cd       = m_world.config.angularDrag;

        return -Cd * strength * m_ang;
    }

    return glm::vec3(0.0f);
}






fsim::Aircraft::Aircraft( fsim::PhysicsWorld &world, const glm::vec3 &pos)
:   RigidBodyComposite(world, pos)
{
    m_min = Aircraft_ctl(-0.5f); m_min.thrust = -16.0f;
    m_max = Aircraft_ctl(+0.5f); m_max.thrust = +256.0f;
    m_spd = Aircraft_ctl( 0.5f);

    m_body  = pushComponent<RigidBody>(glm::vec3( 0.0,  0.0,  4.0),  glm::vec3(1.5,  1.05,  16.0));
    m_lwing = pushComponent<ControlSurface>(glm::vec3(-4.0, 0.0, 0.0), glm::vec3(1.0));
    m_rwing = pushComponent<ControlSurface>(glm::vec3(+4.0, 0.0, 0.0), glm::vec3(1.0));
    m_tail  = pushComponent<RigidBody>(glm::vec3( 0.0,  0.0, +8.5),  glm::vec3(0.5,   5.0,  2.0));
}



void
fsim::Aircraft::update( idk::EngineAPI &api )
{
    float dt = api.dtime();

    if (idkio::keyDown(idk::Keycode::I))
    {
        m_curr.thrust = m_max.thrust; // idk::flerp(m_curr.thrust, m_max.thrust, dt, m_spd.thrust);
    }

    if (idkio::keyDown(idk::Keycode::K))
    {
        m_curr.thrust = m_min.thrust; // idk::flerp(m_curr.thrust, m_min.thrust, dt, m_spd.thrust);
    }

    if (idkio::keyDown(idk::Keycode::DOWN))
    {
        m_curr.pitch = m_max.pitch; // idk::flerp(m_curr.pitch, m_max.pitch, dt, m_spd.pitch);
    }

    if (idkio::keyDown(idk::Keycode::UP))
    {
        m_curr.pitch = m_min.pitch; // idk::flerp(m_curr.pitch, m_min.pitch, dt, m_spd.pitch);
    }

    if (idkio::keyDown(idk::Keycode::U))
    {
        m_curr.roll = m_max.roll; // idk::flerp(m_curr.pitch, m_max.pitch, dt, m_spd.pitch);
    }

    if (idkio::keyDown(idk::Keycode::O))
    {
        m_curr.roll = m_min.roll; // idk::flerp(m_curr.pitch, m_min.pitch, dt, m_spd.pitch);
    }

    if (idkio::keyDown(idk::Keycode::RIGHT))
    {
        m_curr.yaw = m_max.yaw; // idk::flerp(m_curr.yaw, m_max.yaw, dt, m_spd.yaw);
    }

    if (idkio::keyDown(idk::Keycode::LEFT))
    {
        m_curr.yaw = m_min.yaw; // idk::flerp(m_curr.yaw, m_min.yaw, dt, m_spd.yaw);
    }


    for (int i=0; i<5; i++)
    {
        // m_trgt.data[i] = glm::clamp(m_trgt.data[i], m_min.data[i], m_max.data[i]);
        // m_curr.data[i] = idk::flerp(m_curr.data[i], 0.0f, dt, m_spd.data[i]);
        m_curr.data[i] *= 0.8f;
    }


    m_lwing->setPitch(m_curr.pitch + m_curr.roll);
    m_rwing->setPitch(m_curr.pitch - m_curr.roll);

    // {
    //     auto euler = glm::eulerAngles(m_lwing2->getLocalRotation());
    //     euler.x = m_curr.pitch + m_curr.roll;
    //     m_lwing2->getLocalRotation() = glm::quat(euler);
    // }

    // {
    //     auto euler = glm::eulerAngles(m_rwing2->getLocalRotation());
    //     euler.x = m_curr.pitch - m_curr.roll;
    //     m_rwing2->getLocalRotation() = glm::quat(euler);
    // }

    // std::cout << RigidBodyComposite::m_curr.pos.y << "\n";

    {
        auto euler = glm::eulerAngles(m_tail->getLocalRotation());
        euler.y = m_curr.yaw;
        m_tail->getLocalRotation() = glm::quat(euler);
    }

}


void
fsim::Aircraft::integrate()
{
    m_lwing->addPointForceLocal(glm::vec3(0.0, 0.0, -m_curr.thrust), glm::vec3(0.0, 0.1, 0.0));
    m_rwing->addPointForceLocal(glm::vec3(0.0, 0.0, -m_curr.thrust), glm::vec3(0.0, 0.1, 0.0));
    // m_tail->addForceLocal(glm::vec3(0.0, 0.0, -m_curr.thrust));
    // m_body->addPointForceLocal(glm::vec3(0.0, 0.0, -m_curr.thrust), glm::vec3(0.0));

    fsim::RigidBodyComposite::integrate();
}

