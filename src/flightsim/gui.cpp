#include "gui.hpp"
#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>
#include "game-ui/gameui.hpp"
#include "game-ui/inventory.hpp"
#include "player.hpp"


fsim::ElementFlightVector *flightVectors;
fsim::CharacterInventoryGUI *inv;

evo::GUI::GUI()
{
    using namespace spstyle;

    m_LM = new idkui::LayoutManager("assets/font/RodettaStamp.ttf", 24);
    m_root = new idkui::Grid(3, 3, root_style);


    flightVectors = new fsim::ElementFlightVector(nullptr);
    inv = new fsim::CharacterInventoryGUI();
    
    m_root->children[0] = flightVectors;
    m_root->children[1] = inv;

    // auto *list = new idkui::List(grid_style, {
    //     new idkui::Button("Button 1", button_style, buttontext_style),
    //     new idkui::Button("Button 2", button_style, buttontext_style),
    //     new idkui::Button("Button 3", button_style, buttontext_style)
    // });

    // m_root->children[0] = list;


    idk::glTextureConfig config = {
        .internalformat = GL_RGBA8,
        .format         = GL_RGBA,
        .minfilter      = GL_LINEAR,
        .magfilter      = GL_LINEAR,
        .datatype       = GL_UNSIGNED_BYTE,
        .genmipmap      = GL_FALSE
    };
    uint32_t texture = idk::gltools::loadTexture("assets/img/crosshair.png", config);


    auto btn = []( std::string label )
    {
        return new idkui::Button(label, button_style, buttontext_style);
    };

    auto *img  = new idkui::Image(texture, grid_style);
    auto *grid = new idkui::Grid(7, 5, root_style);

    grid->getChild(0, 0) = img;
    grid->getChild(0, 1) = btn("1");
    grid->getChild(0, 2) = btn("2");
    grid->getChild(0, 3) = btn("3");
    grid->getChild(0, 4) = btn("4");


    // m_root = grid;

    m_crosshair = new idkui::ImageAbsolute(texture, root_style);
    m_prompt    = new idkui::TextAbsolute("", buttontext_style);

    m_root->children[4] = m_crosshair;
}


void
evo::GUI::update( idk::EngineAPI &api, evo::Player *player )
{
    auto &ren = api.getRenderer();
    auto *LM = m_LM;

    flightVectors->m_vehicle = player->vehicle;
    inv->openCharacterInventory(player);

    const glm::vec2 winsize = ren.winsize();

    glm::vec3 dlook = glm::vec3(32, 32, 1) * player->dlook();
    glm::vec3 dmove = glm::vec3(4, 4, 4) * player->dmove();

    m_crosshair->setPosition(winsize/2.0f);
    m_crosshair->setScale(glm::vec2(0.5f * player->crosshair_scale));

    if (player->crosshair_enabled == false)
    {
        m_crosshair->setScale(glm::vec2(0.0f));
    }

    m_crosshair->addOffset(glm::vec2(dlook.x, dlook.y));
    m_crosshair->addOffset(glm::vec2(-dmove.x, dmove.y));
    m_crosshair->updateLayout(glm::vec2(0.0f), winsize, 1);

    if (player->prompt != "")
    {
        m_prompt->m_label = player->prompt;
        m_prompt->setPosition(winsize/2.0f);
        m_root->children[4] = m_prompt;
    }

    else
    {
        m_prompt->setPosition(winsize/2.0f);
        m_root->children[4] = m_crosshair;
    }

    m_root->updateLayout(glm::vec2(0.0f), winsize, 1);

    LM->clearTexture(api, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    LM->updateInput(m_root);
    LM->renderNode(m_root);
    LM->renderTexture(api);
}

