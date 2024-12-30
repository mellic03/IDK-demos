#include "state.hpp"
#include "watercraft.hpp"


void
demo::StateGroup::update( idk::EngineAPI &api )
{
    for (const auto &name: m_active)
    {
        dynamic_cast<demo::State*>(m_states[name])->update(api);
    }
}




demo::StateMainMenu::StateMainMenu()
{
    m_LM = new idkui::LayoutManager("assets/font/RodettaStamp.ttf", 24);
    m_ui = new idkui::Grid(3, 3, idkui::Style());
}


void
demo::StateMainMenu::update( idk::EngineAPI &api )
{
    idk::GameState::update();

    // // m_LM->updateInput(world->ui.menu_ui->top());

    // m_LM->clearTexture(api, GL_DEPTH_BUFFER_BIT);
    // m_LM->renderNode(m_ui);
    // m_LM->renderTexture(api);
}





demo::StateGameplay::StateGameplay()
:   m_player()
{
    m_actors.push_back(&m_player);
    m_actors.push_back(new demo::WaterCraft);
}


void
demo::StateGameplay::update( idk::EngineAPI &api )
{
    idk::GameState::update();

    for (auto *A: m_actors)
    {
        A->update(api);
    }

}

