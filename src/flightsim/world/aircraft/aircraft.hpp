#pragma once

#include <flightsim/world/world/vehicle.hpp>
#include <IDKPhysics/body/rigidbody.hpp>
#include <IDKPhysics/body/airfoil.hpp>


namespace idk
{
    struct AircraftCtl;
    class Aircraft;
}


struct idk::AircraftCtl
{
    int   flaps    = 0;
    float throttle = 0.0f;
    float pitch    = 0.0f;
    float roll     = 0.0f;
    float yaw      = 0.0f;
};



class idk::Aircraft: public idk::Vehicle
{
protected:
    AircraftCtl m_ctl;
    phys::RigidBody *m_body;

    int  m_callback_id;
    void _joystick_callback( uint8_t, float );

    
public:
    // using Vehicle::Vehicle;
    Aircraft( idk::EngineAPI&, idk::World&, const glm::vec3& );
    ~Aircraft();

    auto *getBody() { return m_body; }
    auto &getCtl()  { return m_ctl;  }

};