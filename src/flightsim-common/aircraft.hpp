#pragma once

#include <glm/glm.hpp>
#include "physics/compositebody.hpp"


namespace idk
{
    class EngineAPI;
}


namespace fsim
{
    struct Aircraft_ctl;
    class ControlSurface;
    class Aircraft;
}



struct fsim::Aircraft_ctl
{
    union 
    {
        struct
        {
            float pitch;
            float roll;
            float yaw;
            float flaps;
            float thrust;
        };

        struct
        {
            float data[5];
        };
    };
    
    Aircraft_ctl( float f = 0.0f )
    {
        for (int i=0; i<5; i++)
        {
            data[i] = f;
        }
    }
};



class fsim::ControlSurface: public RigidBodyComposite
{
private:
    RigidBody *m_body, *m_aileron;

public:
    ControlSurface( fsim::PhysicsWorld&, const glm::vec3 &pos );

    virtual glm::vec3 computeLinearDrag() override;
    virtual glm::vec3 computeAngularDrag() override;

    void setPitch( float f )
    {
        auto euler = glm::eulerAngles(m_aileron->getLocalRotation());
             euler.x = f;

        m_aileron->getLocalRotation() = glm::quat(euler);
    }

};


class fsim::Aircraft: public fsim::RigidBodyComposite
{
private:
    RigidBody *m_body, *m_tail;
    ControlSurface *m_rwing;
    ControlSurface *m_lwing;

    Aircraft_ctl m_min;
    Aircraft_ctl m_max;
    Aircraft_ctl m_spd;
    Aircraft_ctl m_curr;
    Aircraft_ctl m_trgt;

    std::vector<ControlSurface*> m_surfaces;


public:
    Aircraft( fsim::PhysicsWorld&, const glm::vec3 &pos );

    virtual void integrate() override;
    virtual void update( idk::EngineAPI& );
    // virtual void render( idk::EngineAPI& );

    void setPitch  ( float f ) { m_trgt.pitch  = f; };
    void setRoll   ( float f ) { m_trgt.roll   = f; };
    void setYaw    ( float f ) { m_trgt.yaw    = f; };
    void setFlaps  ( float f ) { m_trgt.flaps  = f; };
    void setThrust ( float f ) { m_trgt.thrust = f; };

    void addPitch  ( float f ) { m_trgt.pitch  += f; };
    void addRoll   ( float f ) { m_trgt.roll   += f; };
    void addYaw    ( float f ) { m_trgt.yaw    += f; };
    void addFlaps  ( float f ) { m_trgt.flaps  += f; };
    void addThrust ( float f ) { m_trgt.thrust += f; };

};



