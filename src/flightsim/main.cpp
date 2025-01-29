#include <iostream>

#include <IDKGraphics/UI/idk_ui.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-gui.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <IDKPhysics/body/airfoil.hpp>

#include "game.hpp"
#include "gui.hpp"
#include "dev-ui/dev-ui.hpp"

#include <flightsim/world/world/item.hpp>
#include <flightsim/world/world/world.hpp>
#include <flightsim/world/world/vehicle.hpp>
#include <flightsim/world/character/npc.hpp>
#include <flightsim/world/character/creature.hpp>
#include <flightsim/world/weapon/weapon.hpp>
#include <flightsim/world/aircraft/helicopter.hpp>
#include <flightsim/world/aircraft/plane.hpp>

#include <IDKBuiltinUI/EditorUI.hpp>

#include "player.hpp"



void
DemoFlightsim::setup( idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ecs    = api.getECS();
    auto &ren    = api.getRenderer();

    idk::RuntimeScript::setCompilerLib("-lFlightSim");

    int id = api.getEngine().registerModule("IDKGE/modules/libIDKBuiltinUI");
    auto &mod = api.getEngine().getModule<EditorUI_MD>(id);

    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::rigid_bodies(api, *(world->physworld)); });
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::constraints(api, *(world->physworld)); });
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::world_settings(api, *(world->physworld)); });
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::entities(api, *world); });
    mod.insertImGui([this](idk::EngineAPI &api) { EvoDevUI::scripts(api); });

    if (gameui == nullptr)
    {
        gameui = new evo::GUI();
    }

    if (world)
    {
        delete world;
    }

    // idk::phys::createRope(*physworld);

    world = new idk::World(api);
    player = world->createActor<evo::Player>(glm::vec3(0.0f, 16.0f, 0.0f));
    auto *V = world->createActor<idk::Helicopter>(glm::vec3(2.0f, 8.0f, -1.3f));
    // auto *V = world->createActor<idk::FighterJet>(glm::vec3(2.0f, 8.0f, -1.3f));
    V->drive(player);

    world->physworld->createBody<phys::StaticBody>(glm::vec3(0.0f), new phys::ShapeHeightmap());

    // player->equipItem(world->createItem<idk::WeaponAK47>());
    // idk::phys::createRope(*world->physworld, V->getBody());

    world->createActor<idk::NPC>(glm::vec3(-2.0f, 2.0f, -2.0f));
    world->createActor<idk::NPC>(glm::vec3(+2.0f, 2.0f, -2.0f));


    int obj = ecs.createGameObject("Terrain", false);
    ecs.giveComponent<idk::TerrainCmp>(obj);
    ecs.getComponent<idk::TransformCmp>(obj).transform.position = glm::vec3(0, -700, 0);
    ecs.getComponent<idk::TransformCmp>(obj).transform.scale    = glm::vec4(2222, 1, 1, 1);
}


void
DemoFlightsim::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &io  = api.getIO();
    auto &ren = api.getRenderer();
    float dt  = api.dtime();

    for (auto *B: world->physworld->rigidBodies())
    {
        ren.drawSphere(B->getRenderMatrix(), B->getRenderMatrixPrev());
    
        for (auto *C: B->m_children)
        {
            ren.drawSphere(C->getRenderMatrix(), C->getRenderMatrixPrev());
        }
    }

    world->render(ren);
    world->update(dt);

    gameui->update(api, player);
}


void
DemoFlightsim::shutdown()
{
    LOG_INFO() << "DemoFlightsim::shutdown";
    // delete gameui;
    // delete world;
}
