#include "world.hpp"
#include "character.hpp"
#include "item.hpp"
#include <IDKIO/IDKIO.hpp>

// #include <libidk/idk_cppscript.hpp>
// static idk::RuntimeScript *config_script = nullptr;


idk::World::World( idk::EngineAPI &api )
:   m_api(api)
{
    physworld = new idk::phys::World();
    physworld->config.gravity.y = -9.8f;
    physworld->config.fluid_density = 0.95f;

    // config_script = new idk::RuntimeScript("assets/scripts/weapon-config");
}


idk::World::~World()
{
    for (Actor *A: m_actors)
    {
        delete A;
    }

    for (auto &[id, I]: m_items)
    {
        m_items.destroy(id);
    }
}


void
idk::World::update( float dt )
{
    // if (m_api.getIO().keyTapped(idk::Keycode::P))
    //     config_script->reload();

    // if (config_script->is_ready() == false)
    // {
    //     return;
    // }

    // config_script->execute(m_api, nullptr);

    for (idk::Actor *A: m_actors)
    {
        A->update();
    }

    for (auto &[id, I]: m_items)
    {
        if (I)
        {
            I->update();
        }
    }

    physworld->update(dt);
}


void
idk::World::render( idk::RenderEngine &ren )
{
    for (idk::Actor *A: m_actors)
    {
        A->render(ren);
    }

    for (auto &[id, I]: m_items)
    {
        I->render(ren);
    }

    // for (auto *B: physworld->rigidBodies())
    // {
    //     ren.drawSphere(B->getRenderMatrix(), B->getRenderMatrixPrev());
    
    //     for (auto *C: B->m_children)
    //     {
    //         ren.drawSphere(C->getRenderMatrix(), C->getRenderMatrixPrev());
    //     }
    // }

    for (auto &[id, C]: physworld->constraints())
    {
        glm::vec3 Apos = C->getBodyA()->state.pos;
        glm::vec3 Bpos = C->getBodyB()->state.pos;
        float mass = glm::min(C->getBodyA()->getMass(), C->getBodyB()->getMass());
        ren.drawLine(Apos, Bpos, mass);
    }
}


void
idk::World::removeActor( int id )
{

}


void
idk::World::removeItem( int id )
{
    Item *I = m_items.get(id);
    removeItem(I);
}


void
idk::World::removeItem( Item *I )
{
    if (I == nullptr)
    {
        return;
    }

    int id  = I->itemID();
    Character *owner = I->getOwner();

    if (owner)
    {
        if (owner->equippedItem() == I)
        {
            owner->equipItem(nullptr);
        }

        int idx = -1;

        for (int i=0; i<owner->m_items.size(); i++)
        {
            if (owner->m_items[i] == I)
            {
                idx = i;
                break;
            }
        }

        if (idx != -1)
        {
            owner->m_items[idx] = nullptr;
        }
    }

    m_items.destroy(id);
}

