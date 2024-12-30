#include <libidk/idk_gamestate.hpp>
#include <IDKGraphics/UI/idk_ui.hpp>
#include <demo-common/player.hpp>


namespace demo
{
    class State;
    class StateGroup;

    class StateMainMenu;
    class StateGameplay;
}



class demo::State: public idk::GameState
{
public:
    virtual void update( idk::EngineAPI& ) = 0;
};


class demo::StateGroup: public idk::GameStateGroup
{
public:
    virtual void update( idk::EngineAPI& );
};



class demo::StateMainMenu: public demo::State
{
private:
    idkui::LayoutManager *m_LM;
    idkui::Grid *m_ui;

public:
    StateMainMenu();
    virtual void update( idk::EngineAPI& );

};



class demo::StateGameplay: public demo::State
{
private:
    demo::Player m_player;
    std::vector<idk::Actor*> m_actors;

public:
    StateGameplay();
    virtual void update( idk::EngineAPI& );

};

