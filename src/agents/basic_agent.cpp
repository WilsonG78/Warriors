#include <entt/entt.hpp>

#include <agents/components.h>

/**
 * @brief creates basic agent in registry
 * @return created entity
 */
entt::entity basic_agent(entt::registry &registry)
{
    const auto entity = registry.create();

    registry.emplace<position>(entity, 0.f, 0.f);
    registry.emplace<velocity>(entity, 0.f, 0.f);
    registry.emplace<orientation>(entity, 0.f);
    registry.emplace<size>(entity, 1.f);
    registry.emplace<side>(entity, SIDE0);

    return entity;
}