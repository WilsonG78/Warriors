#include <float.h>
#include <entt/entt.hpp>

#include <movement/spatial_grid.h>
#include <simulation/observation.h>
#include <agents/components.h>
#include <agents/utils.h>

void update_observation_for_soldiers(entt::registry &registry)
{
    auto view = registry.view<
        closestEnemy,
        alliesInRadius,
        enemiesInRadius,
        const position,
        const perception,
        const side>();

    for(auto [entity, closest, allies, enemies, pos, perc, s]: view.each()) {
        closest.distance = FLT_MAX;
        allies.number = 0; allies.panicked = 0; allies.disabled = 0;
        enemies.number = 0; enemies.panicked = 0; enemies.disabled = 0;

        auto grids = registry.ctx().get<Grids>();
        
        grids.get_allies(s).query(pos, perc.allies_perception_radius, [&](entt::entity other) {
            if(entity == other) return;
            position other_pos = registry.get<position>(other);
            float distance = distance_pos(pos, other_pos);
            if(distance > perc.allies_perception_radius) return;
            status stat = registry.get<status>(other);
            allies.number++;
            allies.panicked += stat==PANICKED;
            allies.disabled += stat==DISABLED;
        });
        
        // closest_enemy_search_radius is larger or equal to enemies_perception_radius
        // so we can iterate over a larger one one time
        grids.get_enemies(s).query(pos, perc.closest_enemy_search_radius, [&](entt::entity other) {
            if(entity == other) return;
            position other_pos = registry.get<position>(other);
            float distance = distance_pos(pos, other_pos);
            if(distance > perc.closest_enemy_search_radius) return;
            // update closest enemy (closest_enemy_search_radius)
            if(distance < closest.distance) {
                closest.distance = distance;
                closest.direction = direction_pos(pos, other_pos);
            }
            // update enemies (enemies_perception_radius)
            if(distance < perc.enemies_perception_radius) {
                status stat = registry.get<status>(other);
                enemies.number++;
                enemies.panicked += stat==PANICKED;
                enemies.disabled += stat==DISABLED;
            }
        });
    }
}