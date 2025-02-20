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
idk::Aircraft::_jscallback( uint8_t axis, float value )
{
    // scale value to [0, 1] range
    value = (value + 32768) / (32767 + 32768);

    switch (axis)
    {
        default: break;
        case 0: m_ctl.roll     = 2.0f * (value-0.5f); break;
        case 1: m_ctl.pitch    = 2.0f * (value-0.5f); break;
        case 2: m_ctl.yaw      = 2.0f * (value-0.5f); break;
        case 3: m_ctl.throttle = value; break;
    }
}



idk::Aircraft::Aircraft( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Vehicle(api, world, p),
    m_body(world.physworld->createBody<phys::RigidBody>(p, phys::SHAPE_SPHERE))
{
    auto &io = api.getIO();

    m_callback_id = io.onJoystickAxis(
        [this](uint8_t a, float b) { return _jscallback(a, b); }
    );
}


idk::Aircraft::~Aircraft()
{
    auto &io = m_api.getIO();
    io.removeCallback(m_callback_id);
}
