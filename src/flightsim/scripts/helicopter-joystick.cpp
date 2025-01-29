#include <IDKGameEngine/api.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKIO/IDKIO.hpp>
#include <libidk/idk_math.hpp>

#include <flightsim/world/aircraft/helicopter.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    auto &io = api.getIO();
    // auto &tsys = api.getECS().getSystem<idk::TransformSys>();
    float dt = api.dtime();

    auto *V = static_cast<idk::Helicopter*>(data);

    if (V->driver == nullptr)
    {
        return 0;
    }


    // V->m_roll_force    = 8.0f * (V->m_joystick_values[0] - 0.5f);
    // V->m_pitch_force   = 4.0f * (V->m_joystick_values[1] - 0.5f);
    // V->m_tail_force    = 4.0f * (V->m_joystick_values[2] - 0.5f);
    // V->m_tail_throttle = 2.0f * V->m_joystick_values[2];
    // V->m_main_throttle = 20.0f * V->m_joystick_values[3];

    // if (io.m_joystick_jhat[0] == 1) V->m_cam_pitch -= 0.35;
    // if (io.m_joystick_jhat[0] == 4) V->m_cam_pitch += 0.35;
    // if (io.m_joystick_jhat[0] == 8) V->m_cam_yaw -= 0.35;
    // if (io.m_joystick_jhat[0] == 2) V->m_cam_yaw += 0.35;

    // int cam = V->driver->headObjID();
    // tsys.getTransformCmp(cam).pitch = -V->m_cam_pitch;
    // tsys.getTransformCmp(cam).yaw   = -V->m_cam_yaw;

    // if (io.m_joystick_btndown[0] == true)
    // {
    //     tsys.getLocalPosition(cam) = glm::vec3(0.0, -8.0, 0.0);
    // }

    // else
    // {
    //     tsys.getLocalPosition(cam) = glm::vec3(0.0, 0.0, 0.0);
    // }

    return 0;
}
