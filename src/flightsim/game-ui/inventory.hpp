#pragma once
#include <IDKGraphics/UI/idk_ui.hpp>

namespace idk  { class Character; }
namespace fsim { class CharacterInventoryGUI; }


class fsim::CharacterInventoryGUI: public idkui::Rect
{
private:
    float m_width  = 64.0f;
    float m_height = 256.0f;
    idk::Character *m_character;

public:
    CharacterInventoryGUI();
    virtual void updateLayout( const glm::vec2&, const glm::vec2&, int ) final;
    virtual void render( idkui::UIRenderer& ) final;
    void openCharacterInventory( idk::Character *C ) { m_character = C; }

};
