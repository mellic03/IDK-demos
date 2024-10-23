#include <iostream>
#include "game.hpp"

#include <IDKGraphics/UI/idk_ui.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-script.hpp>


static idkui::LayoutManager *LM = nullptr;


void
DemoMilsim::registerModules( idk::EngineAPI &api )
{
    using namespace idk;

}


void
DemoMilsim::setup( const std::vector<std::string> &args, idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();


    // int obj = ECS2::createGameObject("Script Test", false);
    // ECS2::giveComponent<ScriptCmp>(obj);
    // ScriptSys::assignScript(obj, "assets/scripts/test.cpp");

    static bool editor_mode = false;

    for (auto &arg: args)
    {
        if (arg == "lm")
        {
            editor_mode = true;
        }
    }


    // ren.pushRenderOverlayFill(glm::vec3(0.0f), 0.0f, 6.25f, 0.25f);
    // ren.pushRenderOverlay("assets/dream-demon-logo.png", 0.5f, 4.0f, 0.5f);
}




void
DemoMilsim::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ren    = api.getRenderer();
    float dt     = engine.deltaTime();


    if (idkio::keyTapped(idk::Keycode::SPACE))
    {
        // ren.skipRenderOverlay();
    }


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
DemoMilsim::shutdown()
{
    LOG_INFO() << "DemoMilsim::shutdown";

}
