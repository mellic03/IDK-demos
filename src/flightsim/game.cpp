#include <iostream>

#include <libidk/idk_log.hpp>

#include <IDKGraphics/UI/idk_ui.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-gui.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <IDKThreading/IDKThreading.hpp>

#include "game.hpp"
#include "gui.hpp"
#include "dev-ui/dev-ui.hpp"
#include "player.hpp"

#include <flightsim/world/world/item.hpp>
#include <flightsim/world/world/world.hpp>
#include <flightsim/world/world/vehicle.hpp>
#include <flightsim/world/character/npc.hpp>
#include <flightsim/world/character/creature.hpp>
#include <flightsim/world/weapon/weapon.hpp>
#include <flightsim/world/aircraft/helicopter.hpp>
#include <flightsim/world/aircraft/plane.hpp>

#include <IDKBuiltinUI/EditorUI.hpp>


idk::phys::StaticBody *plane;
static int uiModuleID;


void
DemoFlightsim::registerCallbacks( idk::EngineAPI &api )
{
    auto &mod = api.getEngine().getModule<EditorUI_MD>(uiModuleID);
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::rigid_bodies(api, *(world->physworld)); });
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::constraints(api, *(world->physworld)); });
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::world_settings(api, *(world->physworld)); });
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::entities(api, *world); });
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::devices(api); });
}


void
DemoFlightsim::setup( idk::EngineAPI &api )
{
    using namespace idk;
    LOG_INFO("");

    auto &engine = api.getEngine();
    auto &ecs    = api.getECS();
    auto &ren    = api.getRenderer();

    ecs.registerComponent<evo::PlayerCmp>("Player", "Flightsim");
    ecs.setUserCallback<evo::PlayerCmp>(evo::PlayerCmpDraw);
    idk::RuntimeScript::setCompilerLib("-lFlightSim");

    uiModuleID = api.getEngine().loadModule("IDKGE/modules/libIDKBuiltinUI");
    registerCallbacks(api);


    if (gameui == nullptr)
    {
        gameui = new evo::GUI(api);
    }

    if (world)
    {
        delete world;
    }

    // idk::phys::createRope(*physworld);

    world = new idk::World(api);
    player = world->createActor<evo::Player>(glm::vec3(0.0f, 16.0f, 0.0f));
    // auto *V = world->createActor<idk::Helicopter>(glm::vec3(8.0f, 16.0f, -32.0f));
    auto *V2 = world->createActor<idk::FighterJet>(glm::vec3(-8.0f, 16.0f, -32.3f));

    // world->physworld->config.gravity.y = 0.0f;

    world->physworld->createBody<phys::StaticBody>(glm::vec3(0.0f), phys::SHAPE_HEIGHTMAP);
    plane = world->physworld->createBody<phys::StaticBody>(glm::vec3(0, 0, -32), phys::SHAPE_AABB);
    plane->shape.extents = glm::vec3(128, 4, 1024);
    plane->state.invMass = 0.0f;

    // player->equipItem(world->createItem<idk::WeaponAK47>());
    // idk::phys::createRope(*world->physworld, V->getBody());

    world->createActor<idk::NPC>(glm::vec3(-2.0f, 2.0f, -2.0f));
    world->createActor<idk::NPC>(glm::vec3(+2.0f, 2.0f, -2.0f));


    int obj = ecs.createGameObject("Terrain", false);
    ecs.giveComponent<idk::TerrainCmp>(obj);
    ecs.getComponent<idk::TransformCmp>(obj).transform.position = glm::vec3(0, -700, 0);
    ecs.getComponent<idk::TransformCmp>(obj).transform.scale    = glm::vec4(2222, 1, 1, 1);

    // api.getEvents().on("pause", [this](void*) {
    //     m_paused = !m_paused;
    // });

    world->on(WorldEvent::TOGGLE | WorldEvent::PAUSE, [this](World*) {
        m_paused = !m_paused;
    });
}


void
DemoFlightsim::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &io  = api.getIO();
    auto &ren = api.getRenderer();
    float dt  = api.dtime();

    if (io.keyTapped(idk::Keycode::F5))
    {
        api.getEngine().reloadModule(uiModuleID, [this, &api]() {
            this->registerCallbacks(api);
        });
    }

    ren.drawRect(plane->getRenderMatrix(true));


    world->render(ren);

    if (m_paused == false)
    {
        world->update(dt);
    }

    gameui->update(api, player);

}


void
DemoFlightsim::shutdown()
{
    LOG_INFO("");
    // delete gameui;
    // delete world;
}
