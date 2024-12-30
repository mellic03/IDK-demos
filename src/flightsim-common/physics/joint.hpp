#pragma once

#include "declarations.hpp"


class fsim::RigidJoint
{
public:
    virtual void update() {  };
    virtual void integrate() = 0;
};


class fsim::GlueJoint: public fsim::RigidJoint
{
public:
    RigidBody *bodyA, *bodyB;

    GlueJoint( RigidBody *A, RigidBody *B, const glm::vec3 &offset );
    virtual void update() final;
    virtual void integrate() final;
};

