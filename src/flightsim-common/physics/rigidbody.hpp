#pragma once

#include "declarations.hpp"


class fsim::RigidBody
{

public:
    struct State
    {
        glm::vec3 pos;
        glm::quat rot;

        State( const glm::vec3 &p, const glm::quat &q )
        :   pos(p), rot(q) {  }
    };

protected:
    PhysicsWorld &m_world;

    friend class fsim::RigidBodyComposite;
    friend class fsim::RigidJoint;
    friend class fsim::GlueJoint;
    friend class fsim::HingeJoint;

    State m_local;
    State m_prev;
    State m_curr;
    State m_lerp;

    glm::mat4 m_prev_T;

    glm::vec3 m_vel;
    glm::vec3 m_ang;

    glm::vec3 m_force;
    glm::vec3 m_torque;

    glm::mat3 m_inertia;
    glm::mat3 m_inv_inertia;

    glm::vec3 m_scale;
    float     m_mass;

public:
    bool has_gravity    = false;
    bool auto_integrate = true;

    RigidBody( fsim::PhysicsWorld&, const glm::vec3 &position );
    void interpolateState( float alpha );

    void translate( const glm::vec3 &v ) { m_curr.pos += v; }

    glm::vec3 &getPosition()      { return m_curr.pos;  }
    glm::vec3 &getLocalPosition() { return m_local.pos; }
    void       setLocalPosition( const glm::vec3 &v ) { m_local.pos = v; }

    glm::quat &getRotation()      { return m_curr.rot;  }
    glm::quat &getLocalRotation() { return m_local.rot; }

    void      setScale( const glm::vec3 &scale );
    glm::vec3 getScale() { return m_scale; };

    virtual void      setMass( float mass ) { m_mass = mass; };
    virtual float     getMass() { return m_mass; };

    virtual glm::vec3 getForce()  { return m_force; }
    virtual glm::vec3 getTorque() { return m_force; }

    virtual glm::mat3 getLocalInertiaTensor() { return m_inertia; }
    virtual glm::mat4 getTransform();

    virtual glm::vec3 computeLinearDrag();
    virtual glm::vec3 computeAngularDrag();

    virtual void      update() {  };
    virtual void      integrate();
    virtual void      render( idk::EngineAPI& );

    void addForce( const glm::vec3 &F )
    {
        m_force += F;
    };

    void addForceLocal( const glm::vec3 &F )
    {
        m_force += glm::inverse(m_curr.rot) * F;
    };

    void addPointForceLocal( const glm::vec3 &F, const glm::vec3 &point )
    {
        m_force  += glm::inverse(m_curr.rot) * F;
        m_torque += glm::cross(point, F);
    };

};

