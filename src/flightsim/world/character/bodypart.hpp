#pragma once
#include <vector>
#include <libidk/idk_glm.hpp>

namespace idk
{
    class RenderEngine;
}

namespace idk
{
    namespace mutation
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
    }

    class BodyPart;
    class BodyPartStructural;
    class BodyPartLeg;
    class BodyPartMouth;
}


class idk::BodyPart
{
protected:
    bool _should_mutate( float mutation_rate );
    void _mutate();
    void _copy_children( BodyPart *other, float mutation_rate );

public:
    BodyPart *m_parent = nullptr;
    glm::mat4 m_local  = glm::mat4(1.0f);
    glm::mat4 m_world  = glm::mat4(1.0f);

    std::vector<BodyPart*> m_children;

    virtual void update();
    virtual void render( idk::RenderEngine& );
    virtual BodyPart *copy( float mutation_rate ) = 0;

    void addChild( BodyPart* );
};



class idk::BodyPartStructural: public BodyPart
{
private:

public:
    virtual void render( idk::RenderEngine& ) override;
    virtual BodyPart *copy( float mutation_rate );
};




class idk::BodyPartLeg: public BodyPart
{
private:
    std::vector<glm::vec3> m_joints;
    std::vector<float>     m_dists;
    float                  m_total_dist;

    glm::vec3 _computeHipPosition();
    glm::vec3 _computeFootPosition();


public:
    BodyPartLeg( const glm::vec3 &offset = glm::vec3(0.0) );

    virtual void update() override;
    virtual void render( idk::RenderEngine& ) override;
    virtual BodyPart *copy( float mutation_rate ) override;
};



// class evo::BodyPartMouth: public BodyPart
// {
// private:

// public:
//     // virtual BodyPart *copy( float mutation_rate );
//     // virtual void render( idk::RenderEngine& );
// };