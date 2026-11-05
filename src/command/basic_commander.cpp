#include <entt/entt.hpp>

#include <command/basic_commander.h>
#include <command/components.h>


entt::entity basic_commander(entt::registry &registry)
{
    const auto entity = registry.create();

    return entity;
}

void assign(entt::registry &registry, entt::entity &soldier, entt::entity &commander)
{
    registry.emplace<relationToCommander>(soldier, commander);
}

void create_unit(entt::registry &registry,
                 std::function<entt::entity(entt::registry&)> create_commander,
                 std::function<entt::entity(entt::registry&)> create_soldier,
                 unsigned int count)
{
    auto commander = create_commander(registry);
    for (auto i = 0u; i < count; i++)
    {
        auto soldier = create_soldier(registry);
        assign(registry, soldier, commander);
    }
}