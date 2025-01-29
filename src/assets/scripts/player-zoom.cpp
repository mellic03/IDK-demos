#include <IDKGameEngine/api.hpp>
#include <IDKIO/IDKIO.hpp>
#include <libidk/idk_math.hpp>

#include <flightsim/player-ctl.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    auto &io   = api.getIO();
    float dt   = api.dtime();

    if (io.mouseCaptured() == false)
    {
        return 0;
    }

    auto  &ctl = *static_cast<evo::PlayerCtl*>(data);
    float factor = 0.0f;

    if (io.keyDown(idk::Keycode::Z))
    {
        factor = 1.0f;
    }

    ctl.zoom_factor = idk::flerp(ctl.zoom_factor, factor, dt, 0.25f);

    return 0;
}
