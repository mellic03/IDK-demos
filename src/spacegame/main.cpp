#include <iostream>

#include <IDKGraphics/UI/idk_ui.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-script.hpp>

#include "game.hpp"
#include "vehicle.hpp"


void
DemoSpaceGame::registerModules( idk::EngineAPI &api )
{
    using namespace idk;

    ECS2::registerSystem<sp::VehicleSys>();
    ECS2::registerComponent<sp::VehicleCmp>("Vehicle", "SpaceGame");

}


void
DemoSpaceGame::setup( const std::vector<std::string> &args, idk::EngineAPI &api )
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

    // stategroup.addState(new demo::StateMainMenu, "main-menu", true);
    // stategroup.addState(new demo::StateGameplay, "gameplay",  true);
}



void
DemoSpaceGame::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &ren = api.getRenderer();
    float dt  = api.dtime();

    // stategroup.update(api);
}



void
DemoSpaceGame::shutdown()
{
    LOG_INFO() << "DemoSpaceGame::shutdown";

}
