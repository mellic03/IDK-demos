#include <IDKGameEngine/api.hpp>
#include <IDKIO/IDKIO.hpp>

#include <flightsim/player-ctl.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    auto &io = api.getIO();
    float dt = api.dtime();

    glm::vec3 delta = glm::vec3(0.0f);
    float speed = dt * 8.0f;

    if (io.keyDown(idk::Keycode::W))     delta.z -= 1.0f;
    if (io.keyDown(idk::Keycode::S))     delta.z += 1.0f;
    if (io.keyDown(idk::Keycode::A))     delta.x -= 1.0f;
    if (io.keyDown(idk::Keycode::D))     delta.x += 1.0f;

    if (io.keyDown(idk::Keycode::SPACE)) delta.y += 1.0f;
    if (io.keyDown(idk::Keycode::LCTRL)) delta.y -= 1.0f;

    auto &ctl = *static_cast<evo::PlayerCtl*>(data);
    ctl.dmove = speed*delta;

    return 0;
}
