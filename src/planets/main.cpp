#include <iostream>
#include "game.hpp"

#include <IDKGraphics/UI/idk_ui.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>


static idkui::LayoutManager *LM = nullptr;


void
DemoPlanets::registerModules( idk::EngineAPI &api )
{
    using namespace idk;

}


void
DemoPlanets::setup( const std::vector<std::string> &args, idk::EngineAPI &api )
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
}



void
DemoPlanets::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &ren = api.getRenderer();
    float dt  = api.dtime();


}



void
DemoPlanets::shutdown()
{
    LOG_INFO() << "DemoPlanets::shutdown";

}
