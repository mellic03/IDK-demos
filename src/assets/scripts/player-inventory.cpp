#include <IDKGameEngine/api.hpp>
#include <IDKIO/IDKIO.hpp>

#include <flightsim/player-ctl.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    auto &io = api.getIO();

    if (io.mouseCaptured() == false)
    {
        return 0;
    }

    auto &ctl = *static_cast<evo::PlayerCtl*>(data);

    for (uint32_t i=idk::Keycode::N1; i<idk::Keycode::N9; i++)
    {
        if (io.keyTapped(idk::Keycode(i)))
        {
            ctl.equip_idx = i - idk::Keycode::N1;
        }
    }

    return 0;
}
