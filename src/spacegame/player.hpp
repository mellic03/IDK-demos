#pragma once

#include "actor.hpp"

namespace sp
{
    class Player;
}


class sp::Player: public sp::Actor
{
private:
    int m_camid;

public:
    Player( idk::EngineAPI&, World&, const glm::vec3 &p );
    virtual void update() override;

};



