#include <entt/entt.hpp>
#include <iostream>

#include <agents/basic_agent.h>
#include <agents/components.h>

#include <command/basic_commander.h>
#include <command/components.h>

/**
 * @brief adds agents to registry
 * 
 * currently used to run quick tests,
 * in the future will be expanded to add agents based on scenario
 */
void addAgentsToRegistry(entt::registry &registry)
{
    create_unit(registry, &basic_commander, &basic_agent, 20);
}

int main()
{
    entt::registry registry;
    float time_step = 0.1; // in seconds

    addAgentsToRegistry(registry);

    while(true)
    {
        registry.view<relationToCommander, position>().each([](const auto entity, const auto &relation, const auto &pos) {
            std::cout << "entity " << static_cast<unsigned>(entt::to_integral(entity))
                      << " parent-> "
                      << static_cast<unsigned>(entt::to_integral(relation.parent))
                      << " position -> " << pos.x << " " << pos.y << "\n";
            });
        break;
    }
    return 0;
}
