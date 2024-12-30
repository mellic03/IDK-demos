#pragma once

#include <libidk/idk_gamestate.hpp>


namespace idk
{
    class Actor;
    class CharacterState;
}


class idk::CharacterState: public idk::GameState
{
public:
    void update( idk::Actor* );

};

