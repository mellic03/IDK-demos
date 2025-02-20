#pragma once
#include "common.hpp"
#include "actor.hpp"

#include <libidk/idk_glm.hpp>
#include <vector>


namespace idk
{
    struct CharacterCtl;
}

struct idk::CharacterCtl
{
    glm::vec3 dmove       = glm::vec3(0.0f);
    glm::vec3 dlook       = glm::vec3(0.0f);

    float     move_growth = 0.1f;
    float     move_decay  = 0.9f;
    float     look_growth = 0.98f;
    float     look_decay  = 0.025f;

    bool      crouching   = false;

    bool      aim         = false;
    float     rest_fov    = 90.0f;
    float     zoom_fov    = 30.0f;
    float     zoom_factor = 0.0f;
    int       equip_idx   = 0;
};


class idk::Character: public idk::Actor
{
private:
    friend class idk::World;

protected:
    int m_head_obj;
    CharacterCtl m_ctl;
    std::vector<Item*> m_items;
    std::vector<std::vector<Item*>> m_inventory;
    Item *m_equipped;


public:
    Vehicle *vehicle = nullptr;

    Character( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );
    
    virtual void update() override;

    const int headObjID() { return m_head_obj; }
    const auto &getItems() { return m_items; }
    const auto &getInventory() { return m_inventory; }

    Item *equippedItem();
    void  equipItem( Item* );

    virtual void look( const glm::vec3 &d ) { };
    virtual void move( const glm::vec3 &d ) { };
    virtual void push( const glm::vec3& ) {  };

    CharacterCtl &getCtl() { return m_ctl; }
    glm::vec3 dlook() const { return m_ctl.dlook; };
    glm::vec3 dmove() const { return m_ctl.dmove; };

};


