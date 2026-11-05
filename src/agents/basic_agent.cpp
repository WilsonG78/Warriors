#include <entt/entt.hpp>

#include <agents/components.h>


entt::entity basic_agent(entt::registry &registry)
{
    const auto entity = registry.create();

    registry.emplace<position>(entity, 0.f, 0.f);
    registry.emplace<velocity>(entity, 0.f, 0.f);

    return entity;
}