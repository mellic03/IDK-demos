#pragma once

#include "character.hpp"


class idk::Vehicle: public idk::Actor
{
protected:
    glm::vec3 m_seatpos = glm::vec3(0.0, 8.0, 6.25);

public:
    idk::Character *driver = nullptr;

    Vehicle( idk::EngineAPI&, idk::World&, const glm::vec3& );

    // virtual void look( const glm::vec3& ) override;
    // virtual void move( const glm::vec3& ) override;

    virtual void drive( idk::Character *A );
    virtual void undrive();

    virtual glm::vec3 getSeatPosition() const { return getWorldPosition(); }
};

