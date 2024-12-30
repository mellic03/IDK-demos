#include <iostream>

#include <IDKGraphics/UI/idk_ui.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKECS/ecs1/idk_ecs.hpp>
#include <IDKBuiltinCS/sys-script.hpp>

#include "game.hpp"
#include "world.hpp"
#include "actor.hpp"
#include "player.hpp"


sp::World *world = nullptr;


void
DemoSpaceGame::registerModules( idk::EngineAPI &api )
{
    using namespace idk;

    // ECS2::registerSystem<sp::VehicleSys>();
    // ECS2::registerComponent<sp::VehicleCmp>("Vehicle", "SpaceGame");
    api.getEngine().registerModule("IDKGE/modules/libIDKBuiltinUI");

}


void
DemoSpaceGame::setup( const std::vector<std::string> &args, idk::EngineAPI &api )
{
    using namespace idk;

    auto &engine = api.getEngine();
    auto &ecs    = api.getECS();
    auto &ren    = api.getRenderer();

    if (world)
    {
        delete world;
    }

    world = new sp::World(api);
    world->createActor<sp::Player>(glm::vec3(0.0f, 0.0f, 0.0f));
    world->createActor<sp::ActorVisible>(glm::vec3(0.0f, 2.0f, 0.0f));
}


void
DemoSpaceGame::mainloop( idk::EngineAPI &api )
{
    using namespace idk;

    auto &ren = api.getRenderer();
    float dt  = api.dtime();

    world->update();

}


void
DemoSpaceGame::shutdown()
{
    LOG_INFO() << "DemoSpaceGame::shutdown";

}
