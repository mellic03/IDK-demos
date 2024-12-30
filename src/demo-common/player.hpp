#pragma once

#include "freecam.hpp"


namespace demo
{
    class Player;
}


class demo::Player: public idk::Freecam
{
public:
    Player( const glm::vec3 &pos = glm::vec3(0.0f) );

    virtual void move( const glm::vec3& ) override;
    virtual void look( const glm::vec2& ) override;

};

