#pragma once

#include <demo-common/actor.hpp>


namespace idk
{
    class CharacterEnemy;
    class EnemyStateInitial;
}


class idk::CharacterEnemy: public idk::Actor
{
protected:

public:
    CharacterEnemy( const glm::vec3 &pos = glm::vec3(0.0f) );

    virtual void move( const glm::vec3& ) override;
    virtual void look( const glm::vec2& ) override;

    virtual void moveTo( const glm::vec3& ) override;
    virtual void lookTo( const glm::vec3& ) override;

};

