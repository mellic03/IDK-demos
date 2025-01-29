#pragma once
#include <vector>
#include <libidk/idk_glm.hpp>

namespace idk
{
    class RenderEngine;
}

namespace evo
{
    enum Mutation
    {
        MUT_INCREASE_MUT_RATE,
        MUT_DECREASE_MUT_RATE,
        MUT_TRANSLATE,
        MUT_ROTATE,
        MUT_SCALE,
        MUT_CREATE_CHILD,
        MUT_REMOVE_CHILD,
        MUT_REMOVE_SELF,

        MUT_COUNT,
    };

    class BodyPart;
    class BodyPartStructural;
    class BodyPartMouth;
}


class evo::BodyPart
{
protected:
    bool should_mutate( float mutation_rate );
    void _mutate();

public:
    BodyPart *parent = nullptr;
    glm::mat4 local  = glm::mat4(1.0f);
    glm::mat4 world  = glm::mat4(1.0f);

    std::vector<BodyPart*> children;
    virtual BodyPart *copy( float mutation_rate ) = 0;

    virtual void update();
    virtual void render( idk::RenderEngine& );
};



class evo::BodyPartStructural: public BodyPart
{
private:

public:
    virtual BodyPart *copy( float mutation_rate );
    virtual void render( idk::RenderEngine& );
};



// class evo::BodyPartMouth: public BodyPart
// {
// private:

// public:
//     // virtual BodyPart *copy( float mutation_rate );
//     // virtual void render( idk::RenderEngine& );
// };