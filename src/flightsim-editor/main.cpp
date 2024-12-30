#include <iostream>
#include "game.hpp"
#include <demo-common/freecam.hpp>
#include <flightsim-common/fsim.hpp>

#include <libidk/idk_gamestate.hpp>

#include <IDKGraphics/UI/idk_ui.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKGameEngine/packager.hpp>

#include <IDKIO/IDKIO.hpp>
#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-script.hpp>


static idkui::LayoutManager *LM = nullptr;
static idk::GameStateGroup stategroup;
static idk::Freecam *player = nullptr;

static FlightSim simworld;


void
DemoFlightsimEditor::registerModules( idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();

    engine.registerModule("IDKGE/modules/libIDKBuiltinUI");
}



void
DemoFlightsimEditor::setup( const std::vector<std::string> &args, idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();

    idk::RuntimeScript::setScriptDirectory("./assets/scripts/");
    idk::RuntimeScript::setScriptExtension(".cpp");

    simworld.setup(api);
    player = new idk::Freecam();
}




void
DemoFlightsimEditor::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();
    float dt     = engine.deltaTime();

    simworld.mainloop(api);
}



void
DemoFlightsimEditor::shutdown()
{
    LOG_INFO() << "DemoFlightsimEditor::shutdown";

}
