#include "player.hpp"
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>



sp::Player::Player( idk::EngineAPI &api, World &world, const glm::vec3 &p )
:   Actor(api, world, p)
{
    auto &ecs = api.getECS();
    ecs.setGameObjectName(m_obj, "Player");
}



void
sp::Player::update()
{
    auto &io  = m_api.getIO();
    auto &ren = m_api.getRenderer();
    auto &cam = ren.getCamera();

    glm::vec3 &pos = idk::TransformSys::getLocalPosition(m_obj);

    if (io.keyDown(idk::Keycode::A)) pos.x -= 0.025f;
    if (io.keyDown(idk::Keycode::D)) pos.x += 0.025f;
    if (io.keyDown(idk::Keycode::W)) pos.z -= 0.025f;
    if (io.keyDown(idk::Keycode::S)) pos.z += 0.025f;
    if (io.keyDown(idk::Keycode::SPACE)) pos.y += 0.025f;
    if (io.keyDown(idk::Keycode::LCTRL)) pos.y -= 0.025f;

    // glm::mat4 T = glm::translate(glm::mat4(1.0f), pos);
    glm::mat4 M = idk::TransformSys::getModelMatrix(m_obj);

    cam.setTransform(M);

}