#include "bodypart.hpp"
#include <IDKGraphics/IDKGraphics.hpp>
#include <IDKGraphics/terrain/terrain.hpp>
#include <libidk/idk_random.hpp>
#include <libidk/idk_transformIK.hpp>


void
idk::BodyPart::update()
{
    if (m_parent)
    {
        m_world = m_parent->m_world * m_local;
    }

    else
    {
        m_world = m_local;
    }

    for (auto *child: m_children)
    {
        child->update();
    }
}

void
idk::BodyPart::render( idk::RenderEngine &ren )
{
    for (auto *child: m_children)
    {
        child->render(ren);
    }
}

void
idk::BodyPart::addChild( BodyPart *B )
{
    B->m_parent = this;
    m_children.push_back(B);
}








void
idk::BodyPartStructural::render( idk::RenderEngine &ren )
{
    ren.drawSphere(m_world);

    for (auto *child: m_children)
    {
        child->render(ren);
    }
}

idk::BodyPart*
idk::BodyPartStructural::copy( float mutation_rate )
{
    auto *other = new BodyPartStructural();
    other->m_local = m_local;

    _copy_children(other, mutation_rate);

    // if (other->_should_mutate(mutation_rate))
    // {
    //     other->_mutate();
    // }

    return other;
}







idk::BodyPartLeg::BodyPartLeg( const glm::vec3 &offset )
{
    m_local = glm::translate(glm::mat4(1), offset);

    m_dists = { 0.5f, 0.6f };
    m_total_dist = 0.0f;
    for (float d: m_dists)
    {
        m_total_dist += d;
    }

    m_joints = {
        glm::vec3(0.0),
        glm::vec3(0.5, -0.5, 0.0),
        glm::vec3(0.25, -1.0, 0.0)
    };
}

glm::vec3
idk::BodyPartLeg::_computeHipPosition()
{
    return glm::vec3(m_world * glm::vec4(m_joints[0], 1.0f));
}

void
idk::BodyPartLeg::update()
{
    BodyPart::update();
    idk::IK::FABRIK(m_joints, m_dists, m_total_dist, 2);
}

void
idk::BodyPartLeg::render( idk::RenderEngine &ren )
{
    for (int i=0; i<m_joints.size(); i++)
    {
        glm::vec3 pos = m_world * glm::vec4(m_joints[i], 1.0f);
        ren.drawSphere(pos, 0.5f);
    }

    for (int i=0; i<m_joints.size()-1; i++)
    {
        glm::vec3 &A = m_joints[i];
        glm::vec3 &B = m_joints[i+1];
        ren.drawLine(A, B, 0.25f);
    }
}

idk::BodyPart*
idk::BodyPartLeg::copy( float mutation_rate )
{
    auto *other = new BodyPartLeg();
    other->m_dists = m_dists;
    other->m_local = m_local;

    _copy_children(other, mutation_rate);

    return other;
}









void
idk::BodyPart::_copy_children( BodyPart *other, float mutation_rate )
{
    for (BodyPart *child1: m_children)
    {
        BodyPart *child2 = child1->copy(mutation_rate);
        child2->m_parent = other;
        other->m_children.push_back(child2);
    }
}


bool
idk::BodyPart::_should_mutate( float mutation_rate )
{
    return (mutation_rate < idk::randf(0, 1));
}


void
idk::BodyPart::_mutate()
{
    using enum idk::mutation::Mutation;

    switch (rand() % MUT_COUNT)
    {
        case MUT_TRANSLATE:
            m_local = glm::translate(m_local, idk::randvec3(-0.1f, +0.1f));
        break;

        case MUT_ROTATE:
            m_local = glm::rotate(
                m_local, idk::randf(-M_PI, +M_PI), glm::normalize(idk::randvec3(-0.1f, +0.1f))
            );
        break;

        case MUT_SCALE:
            m_local = glm::scale(m_local, glm::vec3(idk::randf(0.95f, 1.05f)));
        break;

        case MUT_CREATE_CHILD:
        break;

        case MUT_REMOVE_CHILD:
        {
            int idx = rand() % m_children.size();
            std::swap(m_children[idx], m_children.back());
            delete m_children.back();
            m_children.pop_back();
        }
        break;

        case MUT_REMOVE_SELF:
        break;

        default: break;
    }
}
