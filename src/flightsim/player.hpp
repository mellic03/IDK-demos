#pragma once

#include <flightsim/world/world/character.hpp>
#include <flightsim/world/world/item.hpp>
#include <flightsim/world/weapon/weapon.hpp>
#include <string>
#include <functional>

#include "player-ctl.hpp"


namespace evo
{
    class Player;
}


class evo::Player: public idk::Character
{
private:
    int &m_cam;
    glm::vec3 m_dpos = glm::vec3(0.0f);
    PlayerCtl m_ctl;

    int m_equip_idx = 0;
    idk::WeaponFlashlight *m_tool;
    idk::Weapon *m_weapons[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };

public:
    std::vector<std::function<void()>> m_callbacks;
    std::string prompt = "";

    bool  crosshair_enabled = true;
    float crosshair_scale   = 1.0f;

    Player( idk::EngineAPI&, idk::World&, const glm::vec3 &p );

    PlayerCtl &getCtl() { return m_ctl; }

    virtual void update() override;
    virtual void look( const glm::vec3& ) override;
    virtual void move( const glm::vec3& ) override;
    virtual void push( const glm::vec3& ) override;

    idk::WeaponFlashlight *equippedTool();
    void  equipTool( idk::WeaponFlashlight* );

    glm::vec3 getCameraFront();

};



