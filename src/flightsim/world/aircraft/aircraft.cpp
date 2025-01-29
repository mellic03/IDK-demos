#include "aircraft.hpp"
#include <flightsim/world/world/world.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <libidk/idk_math.hpp>


void
idk::Aircraft::_joystick_callback( uint8_t axis, float value )
{
    // scale value to [-0.5, +0.5] range
    value = 0.5f - (value + 32768) / (32767 + 32768);

    switch (axis)
    {
        default: break;
        case 0: m_ctl.roll     = value; break;
        case 1: m_ctl.pitch    = value; break;
        case 2: m_ctl.yaw      = value; break;
        case 3: m_ctl.throttle = value+0.5f; break;
    }
}



idk::Aircraft::Aircraft( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Vehicle(api, world, p),
    m_body(world.physworld->createBody<phys::RigidBody>(p))
{
    auto &io = api.getIO();

    m_callback_id = io.joystickAxisCreateCallback(
        [this](uint8_t axis, float value) { return _joystick_callback(axis, value); }
    );
}


idk::Aircraft::~Aircraft()
{
    auto &io = m_api.getIO();
    io.JoystickAxisRemoveCallback(m_callback_id);

}
