#include "dev-ui.hpp"
#include <IDKIO/IDKIO.hpp>

#include <flightsim/world/world/character.hpp>
#include <flightsim/world/world/vehicle.hpp>
#include <idk_imgui/imgui.hpp>
#include <flightsim/world/aircraft/aircraft.hpp>


void
EvoDevUI::rigid_bodies( idk::EngineAPI &api, idk::phys::World &world )
{
    ImGui::Begin("Rigid Bodies");

    for (auto *B: world.rigidBodies())
    {
        std::string label = "Rigid Body " + std::to_string(B->getID());

        ImGui::PushID(B->getID());
        ImGui::Text(label.c_str());

        auto &pos  = B->state.pos;
        auto &vel  = B->state.linear.vel;
        auto &acc  = B->state.linear.acc;
        auto &avel = B->state.angular.vel;
        auto &aacc = B->state.angular.acc;
        float mass = 1.0f / B->state.invMass;
        float drag = B->state.drag;
        float rest = B->state.restitution;

        ImGui::Checkbox("Static",                 &B->m_static);
        ImGui::InputFloat("Mass",                 &mass);
        ImGui::InputFloat("Drag",                 &drag);
        ImGui::InputFloat("Restitution",          &rest);
        ImGui::DragFloat3("Position",             &pos[0], 0.05f);
        ImGui::DragFloat3("Velocity",             &vel[0]);
        ImGui::DragFloat3("Acceleration",         &acc[0]);
        ImGui::DragFloat3("Angular Velocity",     &avel[0]);
        ImGui::DragFloat3("Angular Acceleration", &aacc[0]);
        // ImGui::DragFloat3("Forces",               &(B->getForce()[0]));

        // if (pos != B->getPosition())
        // {
        //     B->setPosition(pos);
        // }

        if (1.0f/mass != B->state.invMass)
        {
            B->state.invMass = 1.0f/mass;
        }
        if (drag != B->state.drag)
        {
            // B->setMass(drag);
        }

        ImGui::PopID();    
        ImGui::Spacing();
    }

    ImGui::End();

    ImGui::Begin("Static Bodies");

    for (auto *B: world.staticBodies())
    {
        std::string label = "Static Body " + std::to_string(B->getID());

        ImGui::PushID(B->getID());
        ImGui::Text(label.c_str());

        auto &pos  = B->state.pos;
        auto &vel  = B->state.linear.vel;
        auto &acc  = B->state.linear.acc;
        auto &avel = B->state.angular.vel;
        auto &aacc = B->state.angular.acc;
        float mass = 1.0f / B->state.invMass;
        float drag = B->state.drag;
        float rest = B->state.restitution;

        ImGui::InputFloat("Mass",                 &mass);
        ImGui::InputFloat("Drag",                 &drag);
        ImGui::InputFloat("Restitution",          &rest);
        ImGui::DragFloat3("Position",             &pos[0], 0.05f);
        ImGui::DragFloat3("Velocity",             &vel[0]);
        ImGui::DragFloat3("Acceleration",         &acc[0]);
        ImGui::DragFloat3("Angular Velocity",     &avel[0]);
        ImGui::DragFloat3("Angular Acceleration", &aacc[0]);
        // ImGui::DragFloat3("Forces",               &(B->getForce()[0]));

        // if (pos != B->getPosition())
        // {
        //     B->setPosition(pos);
        // }

        if (1.0f/mass != B->state.invMass)
        {
            B->state.invMass = 1.0f/mass;
        }
        if (drag != B->state.drag)
        {
            // B->setMass(drag);
        }

        ImGui::PopID();    
        ImGui::Spacing();
    }

    ImGui::End();
}


void
EvoDevUI::constraints( idk::EngineAPI &api, idk::phys::World &world )
{
    // ImGui::Begin("Constraints");

    // for (auto *C: world.constraints())
    // {
    //     std::string label = "Constraint " + std::to_string(C->getID());

    //     ImGui::PushID(C->getID());

    //     auto *S = dynamic_cast<idk::phys::SpringConstraint*>(C);
    //     auto *D = dynamic_cast<idk::phys::DistanceConstraint*>(C);

    //     if (S)
    //     {
    //         ImGui::Text((label + " (Spring)").c_str());
    //         ImGui::InputFloat("Target distance", &S->target_dist);
    //         ImGui::InputFloat("Springiness",     &S->springiness);
    //         ImGui::InputFloat("Damping",         &S->damping);
    //     }

    //     else if (D)
    //     {
    //         ImGui::Text((label + " (Distance)").c_str());
    //         ImGui::InputFloat("Target distance", &D->target_dist);
    //         ImGui::InputFloat("Damping",         &D->damping);
    //     }


    //     ImGui::PopID();    
    //     ImGui::Spacing();
    // }

    // ImGui::End();
}


void
EvoDevUI::world_settings( idk::EngineAPI &api, idk::phys::World &world )
{
    auto &conf = world.config;

    ImGui::Begin("Physics World");
    ImGui::InputInt("Tickrate", &conf.tickrate);
    ImGui::InputInt("Substeps", &conf.substeps);
    ImGui::InputFloat("Fluid density", &conf.fluid_density);
    ImGui::InputFloat3("Gravity", &(conf.gravity[0]));

    ImGui::End();
}



void
EvoDevUI::entities( idk::EngineAPI &api, idk::World &world )
{
    // ImGui::Begin("Entities");

    // ImGui::SeparatorText("Aircraft");
    // for (auto *A: world.vehicles())
    // {
    //     auto *V = dynamic_cast<idk::Aircraft*>(A);

    //     glm::vec3 up    = V->m_body->getUp();
    //     glm::vec3 right = V->m_body->getRight();
    //     glm::vec3 front = V->m_body->getFront();

    //     float p = 1.0f - glm::abs(glm::dot(front, up));
    //     float r = 1.0f - glm::abs(glm::dot(right, up));

    //     ImGui::Text("Helicopter");
    //     ImGui::Text("Pitch: %.2f", p);
    //     ImGui::Text("Roll: %.2f",  r);
    //     ImGui::Separator();
    // }

    // ImGui::SeparatorText("Items");
    // for (auto &[id, I]: world.items())
    // {
    //     ImGui::PushID(id);
    //     ImGui::Text("Item %d",      id);
    //     ImGui::Text("Name: \"%d\"", api.getECS().getGameObjectName(I->objID()).c_str());
    //     ImGui::Separator();
    //     ImGui::PopID();
    // }

    // ImGui::SeparatorText("Characters");
    // for (auto *A: world.characters())
    // {
    //     int id = A->actorID();
    //     ImGui::PushID(id);
    //     ImGui::Text("Actor %d", id);
    //     ImGui::Text("Obj ID %d", A->objID());
    //     ImGui::Separator();
    //     ImGui::PopID();
    // }

    // ImGui::End();
}


void
EvoDevUI::devices( idk::EngineAPI &api )
{
    ImGui::Begin("Devices");

    auto &io = api.getIO();

    static std::string name;
    static uint16_t data[4] = {0, 0, 0, 0};
    static const char *labels[4] = {"Vendor", "Product", "Version", "Firmware"};

    for (auto &[key, dev]: io.getDevices())
    {
        if (dev->isValid() == false)
        {
            continue;
        }

        if (!dev->getProductInfo(&name, &data[0], &data[1], &data[2], &data[3]))
        {
            name = "Unknown Device";

            for (int i=0; i<4; i++)
            {
                data[i] = 0;
            }
        }

        if (ImGui::BeginTable("IO Devices", 2, ImGuiTableFlags_RowBg))
        {
            ImGui::TableNextRow();
            ImGui::PushID(key);
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Name: %s", name.c_str());

            for (int i=0; i<4; i++)
            {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text(labels[i]);

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%#04x", data[i]);
            }
        
            ImGui::PopID();
            ImGui::EndTable();
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
    }

    ImGui::End();
}
