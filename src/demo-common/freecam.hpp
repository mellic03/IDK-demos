#pragma once

#include "actor.hpp"


namespace idk
{
    class Freecam;
}


class idk::Freecam: public idk::Actor
{
protected:
    int m_cam_obj;

public:
    Freecam( const glm::vec3 &pos = glm::vec3(0.0f), bool drag = true );

    virtual void move( const glm::vec3& ) override;
    virtual void look( const glm::vec2& ) override;

};

