#include <iostream>

#include <IDKGameEngine/idk_engine_api.hpp>
#include <IDKGraphics/terrain/terrain.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKIO/IDKIO.hpp>

#include <demo-common/actor.hpp>
#include <watercraft/watercraft.hpp>

using namespace idk;


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    float dt = api.dtime();
    auto *A  = static_cast<demo::WaterCraft*>(data);


    int obj = A->getID();
    glm::vec3 &pos = TransformSys::getLocalPosition(obj);
    glm::mat4  T   = TransformSys::getModelMatrix(A->getBody());

    glm::vec3 points[4] = {
        T * glm::vec4(-2.0f, -2.0f,   0.0f, 1.0f),
        T * glm::vec4(+2.0f, -2.0f,   0.0f, 1.0f),
        T * glm::vec4( 0.0f,  0.0f, -16.0f, 1.0f),
        T * glm::vec4( 0.0f,  0.0f, +12.0f, 1.0f)
    };

    for (int i=0; i<4; i++)
    {
        points[i].y = TerrainRenderer::waterHeightQuery(points[i].x, points[i].z);
    }


    glm::vec3 right = glm::normalize(points[1] - points[0]);
    glm::vec3 front = glm::normalize(points[3] - points[2]);
    glm::vec3 up    = -glm::cross(right, front);
    glm::mat4 R     = glm::mat4(glm::mat3(right, up, front));

    TransformSys::getTransform(A->getBody()) = Transform::fromGLM(R);

    float dx, dz;

    float h  = idk::TerrainRenderer::waterHeightQuery(pos.x, pos.z, &dx, &dz);
    float dy = dt * (h - (pos.y + 2.0f));

    A->addVel(glm::vec3(-dt * dx, dy, -dt * dz));

    // glm::vec3 front = TransformSys::yaw(A->getBody());
    // TransformSys::yaw(A->getBody(), 0.0f);


    return 0;
}
