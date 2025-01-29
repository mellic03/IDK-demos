#include "gameui.hpp"
#include <flightsim/world/world/vehicle.hpp>
#include <flightsim/world/aircraft/aircraft.hpp>


fsim::ElementFlightVector::ElementFlightVector( idk::Vehicle *A )
:   idkui::Rect (fsim::style::button_style),
    m_horizon   (fsim::style::line_style),
    m_line      (fsim::style::reticle_style),
    m_vehicle   (A)
{
    m_horizon.setCornerAbsolute(glm::vec2(128, 128));
    m_horizon.setSpanAbsolute(glm::vec2(m_width, 8));
    children.push_back(&m_horizon);

    m_line.setCornerAbsolute(glm::vec2(128, 128));
    m_line.setDepthOffset(1);
    m_line.setSpanAbsolute(glm::vec2(m_width, 4));
    children.push_back(&m_line);

    m_style.maxbounds  = glm::vec2(1024);
    m_style.minbounds  = glm::vec2(128);
    m_style2.maxbounds = glm::vec2(1024);
    m_style2.minbounds = glm::vec2(128);

    m_absolute = true;
    setSpanAbsolute(glm::vec2(m_width, m_height));
    setCornerAbsolute(glm::vec2(128, 128));
}


void
fsim::ElementFlightVector::updateLayout( const glm::vec2 &corner, const glm::vec2 &span,
                                          int depth )
{
    if (m_vehicle == nullptr)
    {
        return;
    }

    // auto *A = dynamic_cast<idk::Aircraft*>(m_vehicle);
    // if (A == nullptr)
    // {
    //     return;
    // }

    // float ymin = m_inner_bounds.corner.y;
    // float ymax = m_inner_bounds.corner.y + m_inner_bounds.span.y;

    // m_horizon.setCornerAbsolute(glm::vec2(128, 0.5*(ymin+ymax)+4.0f));

    // glm::vec3 front = A->getFront();
    // glm::vec3 up    = glm::vec3(0, 1, 0);
    // glm::vec3 vel   = A->getBody()->getVelocity();

    // {
    //     float theta = glm::acos(glm::dot(front, up)) - 0.5*M_PI;
    //     float alpha = 0.5f*(ymin+ymax) - 0.5f*(ymax-ymin)*theta;
    //     m_line.setCornerAbsolute(glm::vec2(128, alpha));
    // }

    // Element::updateLayout(corner, span, depth);
}
