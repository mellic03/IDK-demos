#include "bodypart.hpp"
#include <libidk/idk_random.hpp>
#include <IDKGraphics/IDKGraphics.hpp>


bool
evo::BodyPart::should_mutate( float mutation_rate )
{
    return (mutation_rate < idk::randf(0, 1));
}


void
evo::BodyPart::_mutate()
{
    switch (rand() % MUT_COUNT)
    {
        case MUT_TRANSLATE:
            this->local = glm::translate(local, idk::randvec3(-0.1f, +0.1f));
        break;

        case MUT_ROTATE:
            this->local = glm::rotate(
                local, idk::randf(-M_PI, +M_PI), glm::normalize(idk::randvec3(-0.1f, +0.1f))
            );
        break;

        case MUT_SCALE:
            this->local = glm::scale(local, glm::vec3(idk::randf(0.95f, 1.05f)));
        break;

        case MUT_CREATE_CHILD:
        break;

        case MUT_REMOVE_CHILD:
        {
            int idx = rand() % children.size();
            std::swap(children[idx], children.back());
            delete children.back();
            children.pop_back();
        }
        break;

        case MUT_REMOVE_SELF:
        break;

        default: break;
    }
}


void
evo::BodyPart::update()
{
    for (auto *child: children)
    {
        child->world = this->world * child->local;
        child->update();
    }
}


void
evo::BodyPart::render( idk::RenderEngine &ren )
{
    for (auto *child: children)
    {
        child->render(ren);
    }
}




evo::BodyPart*
evo::BodyPartStructural::copy( float mutation_rate )
{
    auto *other = new BodyPartStructural();
    other->local = this->local;

    for (BodyPart *child1: children)
    {
        BodyPart *child2 = child1->copy(mutation_rate);
        child2->parent = other;
        other->children.push_back(child2);
    }

    if (other->should_mutate(mutation_rate))
    {
        other->_mutate();
    }

    return other;
}


void
evo::BodyPartStructural::render( idk::RenderEngine &ren )
{
    ren.drawSphere(this->world);

    for (auto *child: children)
    {
        child->render(ren);
    }
}
