#pragma once
#include "common.hpp"
#include "actor.hpp"
#include "character.hpp"
#include "item.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKGraphics/IDKGraphics.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <libidk/idk_wallocator2.hpp>
#include <libidk/idk_vector2.hpp>
#include <vector>


class idk::World
{
private:
    idk::vector2<Actor*>     m_actors;
    idk::vector2<Character*> m_characters;
    // std::vector<Item*>      m_items;
    idk::WAllocator2<Item>  m_items;
    std::vector<Vehicle*>   m_vehicles;


    idk::EngineAPI &m_api;

public:
    idk::phys::World *physworld;

         World( idk::EngineAPI &api );
        ~World();

    void update( float dt );
    void render( idk::RenderEngine& );

    auto &actors()     { return m_actors;     }
    auto &characters() { return m_characters; }
    auto &vehicles()   { return m_vehicles;   }
    auto &items()      { return m_items;      }

    void removeActor( int id );
    void removeItem( int id );
    void removeItem( Item* );


    template <typename actor_type, typename... Args>
    actor_type *createActor( Args&&... args )
    {
        auto *obj = new actor_type(m_api, *this, std::forward<Args>(args)...);

        if (dynamic_cast<idk::Character*>(obj))
            m_characters.push_back(dynamic_cast<idk::Character*>(obj));

        if (dynamic_cast<idk::Vehicle*>(obj))
            m_vehicles.push_back(dynamic_cast<idk::Vehicle*>(obj));

        m_actors.push_back(dynamic_cast<idk::Actor*>(obj));
        m_actors.back()->m_ID = m_actors.size() - 1;

        return obj;
    }


    template <typename item_type, typename... Args>
    item_type *createItem( Args&&... args )
    {
        auto *I = new item_type(m_api, *this, std::forward<Args>(args)...);
        int id = m_items.create(dynamic_cast<idk::Item*>(I));
        m_items.get(id)->m_ID = id;
        return I;
    }


    template <typename item_type, typename character_type>
    item_type *giveItem( character_type *C )
    {
        IDK_ASSERT(
            "Supplied object does not derive from idk::Character!",
            dynamic_cast<Character*>(C) != nullptr
        );

        auto *I = createItem<item_type>(C);
        C->m_items.push_back(I);
        C->equipItem(I);
    
        return I;
    }


    template <typename item_type, typename character_type>
    void pushItem( character_type *C )
    {
        IDK_ASSERT(
            "Supplied object does not derive from idk::Character!",
            dynamic_cast<Character*>(C) != nullptr
        );

        auto *I = createItem<item_type>(C);
        C->m_items.push_back(I);
    }


    template <typename character_type>
    void popItem( character_type *C )
    {
        IDK_ASSERT(
            "Supplied a nullptr!",
            C != nullptr
        );

        IDK_ASSERT(
            "Supplied object does not derive from idk::Character!",
            dynamic_cast<Character*>(C) != nullptr
        );

        if (C->m_items.size() > 0)
        {
            removeItem(C->m_items.back());
            C->m_items.pop_back();
        }
    }

};

