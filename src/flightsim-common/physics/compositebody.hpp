#pragma once

#include "declarations.hpp"
#include "physicsworld.hpp"
#include "rigidbody.hpp"


class fsim::RigidBodyComposite: public fsim::RigidBody
{
protected:
    std::vector<RigidBody*> m_components;

private:
    glm::vec3 m_COM;

    float     computeCompositeMass();
    glm::vec3 computeCenterOfMass     ( float totalMass );
    glm::vec3 computeCompositeForce   ( float totalMass );
    glm::vec3 computeCompositeTorque  ( float totalMass );
    glm::mat3 computeCompositeInertia ( const glm::vec3 &COM );


public:
    RigidBodyComposite( fsim::PhysicsWorld&, const glm::vec3 &pos );

    virtual void integrate() override;
    virtual void render( idk::EngineAPI& ) override;


    virtual void      setMass( float ) {  };
    virtual float     getMass() { return m_mass; };

    virtual glm::vec3 getForce()  { return computeCompositeForce(m_mass); };
    virtual glm::vec3 getTorque() { return computeCompositeTorque(m_mass); };

    virtual glm::mat3 getLocalInertiaTensor() { return computeCompositeInertia(m_COM); };

    virtual glm::vec3 computeLinearDrag();
    virtual glm::vec3 computeAngularDrag();




    template <typename T>
    T *pushComponent( const glm::vec3 &offset, const glm::vec3 &scale )
    {
        auto *obj = m_world.createBody<T>(glm::vec3(0.0f));
              obj->auto_integrate = false;
              obj->setLocalPosition(offset);
              obj->setScale(scale);

        m_components.push_back(dynamic_cast<RigidBody*>(obj));

        return obj;
    }

};

