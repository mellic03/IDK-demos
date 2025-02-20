#pragma once

#include <flightsim/world/world/character.hpp>
#include <flightsim/world/world/item.hpp>
#include <flightsim/world/weapon/weapon.hpp>
#include <string>
#include <functional>


namespace idk
{
    class ECS;
}

namespace evo
{
    class Player;
    struct PlayerCmp;
    void PlayerCmpDraw( idk::EngineAPI&, idk::ECS&, int );
}


class evo::Player: public idk::Character
{
private:
    int &m_cam;
    glm::vec3 m_dpos = glm::vec3(0.0f);

    int m_equip_idx = 0;
    idk::WeaponFlashlight *m_tool;
    idk::Weapon *m_weapons[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
    idk::Weapon *m_weapon = nullptr;

    std::vector<int> m_callbacks;

    void _setupKeyboardCallbacks();
    void _setupGamepadCallbacks();
    void _keyboardControl();
    void _gamepadControl();



public:
    std::string prompt = "";

    bool  crosshair_enabled = true;
    float crosshair_scale   = 1.0f;

    Player( idk::EngineAPI&, idk::World&, const glm::vec3 &p );
    ~Player();

    virtual void update() override;
    virtual void look( const glm::vec3& ) override;
    virtual void move( const glm::vec3& ) override;
    virtual void push( const glm::vec3& ) override;

    idk::WeaponFlashlight *equippedTool();
    void  equipTool( idk::WeaponFlashlight* );

    glm::vec3 getCameraFront();

};


struct evo::PlayerCmp
{
    int obj_id = -1;
    evo::Player *player;

    size_t serialize( std::ofstream &stream ) const;
    size_t deserialize( std::ifstream &stream );
    static void onObjectAssignment( idk::EngineAPI &api, idk::ECS &ecs, int obj_id );
    static void onObjectDeassignment( idk::EngineAPI &api, idk::ECS &ecs, int obj_id );
    static void onObjectCopy( idk::ECS &ecs, int src_obj, int dst_obj );

};




