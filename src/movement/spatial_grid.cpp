#include <entt/entt.hpp>

#include <movement/spatial_grid.h>
#include <agents/components.h>

/**
 * @brief creates spatial grids for two sides
 * grids are kept in registry.ctx()
 * to get them use registry.ctx().get<Grids>()
 */
void create_grids(entt::registry &registry)
{
    Grids grids;
    registry.ctx().emplace<Grids>(grids);
    auto view = registry.view<const position, const side>();

    for(auto [entity, pos, s]: view.each()) {
        grids.get_allies(s).insert(entity, pos);
    }
}

/**
 * @brief updates grids
 * currently clears each SpatialGrid and then adds entities
 */
void update_grids(entt::registry &registry)
{
    auto view = registry.view<const position, const side>();
    Grids grids = registry.ctx().get<Grids>();

    grids.grid0.clear(); grids.grid1.clear();

    for(auto [entity, pos, s]: view.each()) {
        grids.get_allies(s).insert(entity, pos);
    }
}