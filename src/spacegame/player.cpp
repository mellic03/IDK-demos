#include "player.hpp"
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>



sp::Player::Player( idk::EngineAPI &api, World &world, const glm::vec3 &p )
:   Actor(api, world, p)
{
    
}


void
sp::Player::update()
{
    auto &ren = m_api.getRenderer();
    auto &cam = ren.getCamera();

    if (idkio::keyDown(idk::Keycode::A)) m_pos.x -= 0.025f;
    if (idkio::keyDown(idk::Keycode::D)) m_pos.x += 0.025f;
    if (idkio::keyDown(idk::Keycode::W)) m_pos.z -= 0.025f;
    if (idkio::keyDown(idk::Keycode::S)) m_pos.z += 0.025f;
    if (idkio::keyDown(idk::Keycode::SPACE)) m_pos.y += 0.025f;
    if (idkio::keyDown(idk::Keycode::LCTRL)) m_pos.y -= 0.025f;

    glm::mat4 T = glm::translate(glm::mat4(1.0f), m_pos);

    cam.setTransform(T);

}