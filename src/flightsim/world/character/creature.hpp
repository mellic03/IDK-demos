#pragma once
#include <vector>
#include <libidk/idk_glm.hpp>
#include <flightsim/world/world/character.hpp>
#include "bodypart.hpp"

namespace idk
{
    class RenderEngine;
    class Creature;
}


class idk::Creature: public idk::Character
{
private:
    BodyPart *m_root;
    float m_mutation_rate = 0.0f;

public:
                 Creature( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );
    virtual void update() override;
    virtual void render( idk::RenderEngine& ) override;
    Creature     reproduce(); 

};

