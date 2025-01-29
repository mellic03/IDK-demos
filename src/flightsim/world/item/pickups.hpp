#pragma once
#include <flightsim/world/world/item.hpp>


namespace idk
{
    class PickupHealth;
}


class idk::PickupHealth: public idk::Item
{
private:

public:
    virtual void update() final;
    virtual void render( idk::RenderEngine& ) final;

};


