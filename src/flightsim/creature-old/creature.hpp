#pragma once
#include <vector>
#include <libidk/idk_glm.hpp>
#include "bodypart.hpp"

namespace idk
{
    class RenderEngine;
}

namespace evo
{
    class Creature;
}


class evo::Creature
{
private:
    glm::vec3 m_pos;
    BodyPart *m_root;
    float m_mutation_rate = 0.0f;

public:
             Creature( const glm::vec3 &p );
    void     update();
    void     render( idk::RenderEngine& );
    Creature reproduce(); 

};

