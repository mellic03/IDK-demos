#pragma once

#include "declarations.hpp"
#include "rigidbody.hpp"
#include "joint.hpp"


class fsim::PhysicsConfig
{
public:
    float     timestep = 1.0f / 60.0f;
    glm::vec3 gravity  = glm::vec3(0.0f);

    float linearDrag   = 0.25f;
    float angularDrag  = 0.25f;
    float airDensity   = 1.225f;

    PhysicsConfig() {  };

};



class fsim::PhysicsWorld
{
private:
    std::vector<RigidBody*>  m_bodies;
    std::vector<RigidJoint*> m_joints;
    float       m_accum;

public:
    fsim::PhysicsConfig config;

    PhysicsWorld( const fsim::PhysicsConfig &config = fsim::PhysicsConfig() );
    void update( idk::EngineAPI& );


    template <typename T, typename... Args>
    T *createBody( Args&&... args )
    {
        auto *obj = new T(*this, std::forward<Args>(args)...);
        m_bodies.push_back(dynamic_cast<RigidBody*>(obj));
        return obj;
    }


    template <typename T, typename... Args>
    T *createJoint( Args&&... args )
    {
        auto *obj = new T(std::forward<Args>(args)...);
        m_joints.push_back(dynamic_cast<RigidJoint*>(obj));
        return obj;
    }
};


