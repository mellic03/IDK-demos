#pragma once
#include "common.hpp"
#include "actor.hpp"

#include <libidk/idk_glm.hpp>
#include <vector>


class idk::Character: public idk::Actor
{
private:
    friend class idk::World;
    glm::vec3 m_dlook = glm::vec3(0.0f);
    glm::vec3 m_dmove = glm::vec3(0.0f);

protected:
    int m_head_obj;
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

    virtual void look( const glm::vec3 &d ) { m_dlook += d; };
    virtual void move( const glm::vec3 &d ) { m_dmove += d; };
    virtual void push( const glm::vec3& ) {  };

    glm::vec3 dlook() const { return m_dlook; };
    glm::vec3 dmove() const { return m_dmove; };

};


