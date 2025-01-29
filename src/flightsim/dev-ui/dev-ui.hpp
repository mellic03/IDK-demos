#pragma once

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKECS/IDKECS.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <flightsim/world/world/world.hpp>
#include <flightsim/world/weapon/weapon.hpp>

namespace EvoDevUI
{
    void rigid_bodies( idk::EngineAPI&, idk::phys::World& );
    void constraints( idk::EngineAPI&, idk::phys::World& );
    void world_settings( idk::EngineAPI&, idk::phys::World& );
    void entities( idk::EngineAPI&, idk::World& );
    void scripts( idk::EngineAPI& );
}

