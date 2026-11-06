#include <entt/entt.hpp>


entt::entity basic_commander(entt::registry &registry);
void assign(entt::registry &registry, entt::entity &soldier, entt::entity &commander);
void create_unit(
    entt::registry &registry,
    std::function<entt::entity(entt::registry&)> create_commander,
    std::function<entt::entity(entt::registry&)> create_soldier,
    unsigned int count
);