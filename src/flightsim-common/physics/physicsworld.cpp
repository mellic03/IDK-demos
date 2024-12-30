#include "physicsworld.hpp"
#include "rigidbody.hpp"
#include "joint.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>


fsim::PhysicsWorld::PhysicsWorld( const fsim::PhysicsConfig &config )
:   config(config),
    m_accum(0.0f)
{

}


void
fsim::PhysicsWorld::update( idk::EngineAPI &api )
{
    float timestep = config.timestep;
    m_accum += api.dtime();

    while (m_accum >= timestep)
    {
        for (auto *joint: m_joints)
        {
            joint->integrate();
        }

        for (auto *body: m_bodies)
        {
            body->integrate();
        }

        m_accum -= timestep;
    }


    float alpha = glm::clamp(m_accum / timestep, 0.0f, 1.0f);

    for (auto *joint: m_joints)
    {
        joint->update();
    }

    for (auto *body: m_bodies)
    {
        body->interpolateState(alpha);
        body->update();
        body->render(api);
    }

}


