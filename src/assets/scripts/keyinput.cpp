#include <iostream>

#include <IDKGameEngine/idk_engine_api.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKIO/IDKIO.hpp>

#include <demo-common/actor.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    float dt = api.dtime();
    auto  *A = static_cast<idk::Actor*>(data);


    auto delta = glm::vec3(0.0f);
    float speed = dt * 8.0f;

    if (idkio::keyDown(idk::Keycode::W))     delta.z -= 1.0f;
    if (idkio::keyDown(idk::Keycode::S))     delta.z += 1.0f;
    if (idkio::keyDown(idk::Keycode::A))     delta.x -= 1.0f;
    if (idkio::keyDown(idk::Keycode::D))     delta.x += 1.0f;
    if (idkio::keyDown(idk::Keycode::SPACE)) delta.y += 1.0f;
    if (idkio::keyDown(idk::Keycode::LCTRL)) delta.y -= 1.0f;

    A->move(speed*delta);

    return 0;
}
