#pragma once
#include <libidk/idk_glm.hpp>
#include <flightsim/world/world/character.hpp>

namespace idk
{
    class NPC;
}


class idk::NPC: public idk::Character
{
private:
    int m_model;

protected:

public:
    NPC( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );
    virtual void update();

};


