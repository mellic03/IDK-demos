#include "aircraft.hpp"
#include <flightsim/world/world/world.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKIO/device/joystick.hpp>

#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <libidk/idk_math.hpp>


void
idk::Aircraft::_jscallback( const idk::Joystick &JS )
{
    // m_ctl.roll     = JS.stick.roll;
    // m_ctl.pitch    = JS.stick.pitch;
    // m_ctl.yaw      = JS.stick.yaw;
    // m_ctl.throttle = JS.stick.throttle;

    // if (JS.hat[0] == 1) m_ctl.cam_pitch -= M_PI / 12.0;
    // if (JS.hat[0] == 4) m_ctl.cam_pitch += M_PI / 12.0;
    // if (JS.hat[0] == 8) m_ctl.cam_yaw   -= M_PI / 6.0;
    // if (JS.hat[0] == 2) m_ctl.cam_yaw   += M_PI / 6.0;

}


idk::Aircraft::Aircraft( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Vehicle(api, world, p),
    m_body(world.physworld->createBody<phys::RigidBody>(p, phys::SHAPE_SPHERE))
{
    using JE = idk::JoystickEvent;
    auto &io = api.getIO();

    // auto *jstick = io.openDevice<idk::Joystick>(0);

    // jstick->on(JE::PITCH, [this](Joystick *J) {std::cout << "pitch"; m_ctl.pitch = J->stick.pitch; })
    //        .on(JE::ROLL,  [this](Joystick *J) {std::cout << "roll"; m_ctl.roll  = J->stick.roll;  })
    //        .on(JE::YAW,   [this](Joystick *J) {std::cout << "yaw"; m_ctl.yaw   = J->stick.yaw;   });

}


idk::Aircraft::~Aircraft()
{
    // auto &io = m_api.getIO();
    // io.removeCallback(m_callback_id);
}
