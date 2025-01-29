#include <IDKGameEngine/api.hpp>
#include <IDKIO/IDKIO.hpp>
#include <libidk/idk_math.hpp>

#include <flightsim/player-ctl.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    auto &io = api.getIO();
    float dt = api.dtime();

    auto &ctl = *static_cast<evo::PlayerCtl*>(data);
    ctl.dlook *= 0.0f;

    if (io.keyTapped(idk::Keycode::ESCAPE))
    {
        bool b = io.mouseCaptured();
        io.mouseCapture(!b);
    }

    if (io.mouseCaptured())
    {
        ctl.dlook = 0.15f * 0.005f * glm::vec3(-io.mouseDelta(), 0.0f);
    }

    return 0;
}
