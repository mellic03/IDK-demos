#pragma once

#include <libidk/idk_assert.hpp>
#include <libidk/idk_module.hpp>
#include <libidk/idk_game.hpp>
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <string>

namespace idk
{
    class ECS;
    class World;
}

namespace evo
{
    class GUI;
    class Player;
}


class IDK_VISIBLE DemoFlightsim: public idk::Game
{
private:
    evo::GUI    *gameui   = nullptr;
    idk::World  *world    = nullptr;
    evo::Player *player   = nullptr;
    bool m_paused = false;


public:

    virtual std::string getName() final { return "Evolution"; }

    void registerCallbacks( idk::EngineAPI& );

    // virtual void loadModules ( idk::EngineAPI& ) final;
    virtual void setup           ( idk::EngineAPI& ) final;
    virtual void mainloop        ( idk::EngineAPI& ) final;
    virtual void shutdown        (                 ) final;
};

