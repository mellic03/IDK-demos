#include <iostream>

#include <IDKGraphics/UI/idk_ui.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-script.hpp>

#include "game.hpp"
#include "state.hpp"

static demo::StateGroup stategroup;


void
DemoWaterCraft::registerModules( idk::EngineAPI &api )
{
    using namespace idk;

}


void
DemoWaterCraft::setup( const std::vector<std::string> &args, idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();

    static bool editor_mode = false;

    for (auto &arg: args)
    {
        if (arg == "lm")
        {
            editor_mode = true;
        }
    }

    stategroup.addState(new demo::StateMainMenu, "main-menu", true);
    stategroup.addState(new demo::StateGameplay, "gameplay",  true);
}



void
DemoWaterCraft::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &ren = api.getRenderer();
    float dt  = api.dtime();

    stategroup.update(api);
}



void
DemoWaterCraft::shutdown()
{
    LOG_INFO() << "DemoWaterCraft::shutdown";

}
