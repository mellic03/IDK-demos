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
#include <IDKBuiltinCS/sys-transform.hpp>


static idkui::LayoutManager *LM = nullptr;
static idk::GameStateGroup stategroup;
static idk::Freecam *player = nullptr;

static FlightSim simworld;


void
DemoFlightsim::registerModules( idk::EngineAPI &api )
{
    using namespace idk;

}


void
DemoFlightsim::setup( const std::vector<std::string> &args, idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();

    idk::RuntimeScript::setScriptDirectory("./assets/script_dlib/");
    idk::RuntimeScript::setScriptExtension(IDK_DLIB_EXT);

    simworld.setup(api);
    player = new idk::Freecam(glm::vec3(0.0), true);
}




void
DemoFlightsim::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();
    float dt     = engine.deltaTime();

    simworld.mainloop(api);

    // glm::vec3 &pos = idk::TransformSys::getLocalPosition(player->getID());
    // pos = simworld.m_craft->getPosition() + glm::vec3(8.0f);

    static float accum = 0.0f;
    accum += dt;

    if (accum >= 1.0f / 30.0f)
    {
        // LM->updateInput(world->ui.menu_ui->top());
    
        // LM->clearTexture(api, GL_DEPTH_BUFFER_BIT);
        // LM->renderNode(world->ui.onscreen_text);
        // LM->renderTexture(api);
    }

}



void
DemoFlightsim::shutdown()
{
    LOG_INFO() << "DemoFlightsim::shutdown";

}
