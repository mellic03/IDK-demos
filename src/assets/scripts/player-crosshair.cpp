#include <IDKGameEngine/api.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKIO/IDKIO.hpp>

#include <IDKGraphics/UI/idk_ui.hpp>
#include <flightsim/player.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    auto &ren = api.getRenderer();
    auto &io = api.getIO();
    float dt = api.dtime();

    const glm::vec2 winsize = ren.winsize();

    using dtype = std::pair<evo::Player*, idkui::ImageAbsolute*>;
    auto [P, img] = *static_cast<dtype*>(data);

    glm::vec3 dlook = glm::vec3(32, 32, 1) * P->dlook();
    glm::vec3 dmove = glm::vec3(4, 4, 4) * P->dmove();

    img->setPosition(winsize/2.0f);
    img->setScale(glm::vec2(0.5f * P->crosshair_scale));
    img->addOffset(glm::vec2(dlook.x, dlook.y));
    img->addOffset(glm::vec2(-dmove.x, dmove.y));

    if (P->crosshair_enabled == false)
    {
        img->addOffset(glm::vec2(-4096));
    }

    return 0;
}
