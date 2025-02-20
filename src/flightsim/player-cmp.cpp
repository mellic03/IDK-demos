#include "player.hpp"
#include <libidk/idk_serialize.hpp>
#include <IDKECS/IDKECS.hpp>
#include <idk_imgui/imgui.hpp>



void
evo::PlayerCmpDraw( idk::EngineAPI &api, idk::ECS &ecs, int obj_id )
{
    auto &cmp = ecs.getComponent<evo::PlayerCmp>(obj_id);
    auto *player = cmp.player;
    auto &ctl = player->getCtl();

    ImGui::InputFloat("Move growth", &ctl.move_growth);
    ImGui::InputFloat("Move decay",  &ctl.move_decay);

    ImGui::InputFloat("Look growth", &ctl.look_growth);
    ImGui::InputFloat("Look decay",  &ctl.look_decay);

}





size_t
evo::PlayerCmp::serialize( std::ofstream &stream ) const
{
    size_t n = 0;
    n += idk::streamwrite(stream, obj_id);

    return n;
}


size_t
evo::PlayerCmp::deserialize( std::ifstream &stream )
{
    size_t n = 0;
    n += idk::streamread(stream, obj_id);

    return n;
}


void
evo::PlayerCmp::onObjectAssignment( idk::EngineAPI &api, idk::ECS &ecs, int obj_id )
{

}


void
evo::PlayerCmp::onObjectDeassignment( idk::EngineAPI &api, idk::ECS &ecs, int obj_id )
{
    auto &cmp = ecs.getComponent<PlayerCmp>(obj_id);

}


void
evo::PlayerCmp::onObjectCopy( idk::ECS &ecs, int src_obj, int dst_obj )
{

}




