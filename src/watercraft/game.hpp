#pragma once

#include <libidk/idk_assert.hpp>
#include <libidk/idk_module.hpp>
#include <libidk/idk_game.hpp>

#include <string>


class IDK_VISIBLE DemoWaterCraft: public idk::Game
{
public:
    virtual std::string getName() final { return "WaterCraft"; }

    virtual void registerModules ( idk::EngineAPI& ) final;
    virtual void setup           ( const std::vector<std::string>&, idk::EngineAPI& ) final;
    virtual void mainloop        ( idk::EngineAPI& ) final;
    virtual void shutdown        (                 ) final;

};

