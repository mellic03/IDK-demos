#include "inventory.hpp"
#include <flightsim/world/world/character.hpp>


static idkui::Style bruh = {
    .margin  = glm::vec4(2.0f),
    .padding = glm::vec4(2.0f),
    .radius  = glm::vec4(8.0f),
    .fg      = glm::vec4(0.9, 0.9, 0.9, 1.0),
    .bg      = glm::vec4(0, 0, 0, 1),
    .minbounds = glm::vec2(0.0f, 64.0f),
    .maxbounds = glm::vec2(+INFINITY, 64.0f)
};


fsim::CharacterInventoryGUI::CharacterInventoryGUI()
:   idkui::Rect(bruh)
{
    m_style.maxbounds  = glm::vec2(1024);
    m_style.minbounds  = glm::vec2(256);
    m_style2.maxbounds = glm::vec2(1024);
    m_style2.minbounds = glm::vec2(256);

    m_absolute = true;
    setSpanAbsolute(glm::vec2(512, 512));
    setCornerAbsolute(glm::vec2(128, 128));
}


void
fsim::CharacterInventoryGUI::updateLayout( const glm::vec2 &corner, const glm::vec2 &span,
                                          int depth )
{
    if (m_character == nullptr)
    {
        return;
    }

    auto *C = m_character;
    auto &in = C->getInventory();

}


void
fsim::CharacterInventoryGUI::render( idkui::UIRenderer &ren )
{
    float square_width = 32.0f;
    glm::vec4 bg = glm::vec4(0.2, 0.2, 0.2, 1.0);

    if (m_character == nullptr)
    {
        return;
    }

    auto &in = m_character->getInventory();

    for (int i=0; i<in.size(); i++)
    {
        float y = 128.0f + square_width*i;

        for (float j=0; j<in[i].size(); j++)
        {
            float x = 128.0f + square_width*j;

            idkui::Primitive p0 = {
                .corner = glm::vec2(x+4, y+4),
                .span   = glm::vec2(32-4),
                .depth  = 8,
                .radius = glm::vec4(8.0f)
            };
        
            ren.renderPrimitive(p0, bg);
        }
    }

}
