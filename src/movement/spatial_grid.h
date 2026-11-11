#ifndef MOVEMENT_SPATIAL_GRID_H
#define MOVEMENT_SPATIAL_GRID_H

#include <entt/entt.hpp>

#include <agents/components.h>

/**
 * @brief divides world into cells
 * supports positions from cell_size*MIN_INT to cell_size*MAX_INT
 */
struct SpatialGrid {
    float cell_size;
    std::unordered_map<std::int64_t, std::vector<entt::entity>> cells;

    int  idx(float v) const { return static_cast<int>(std::floor(v / cell_size)); }
    static std::int64_t key(int cx, int cy) {
        return (std::int64_t(cx) << 32) | std::uint32_t(cy);
    }

    void clear() { for (auto& [k, v] : cells) v.clear(); }
    void insert(entt::entity e, position pos) { cells[key(idx(pos.x), idx(pos.y))].push_back(e); }

    template<class F>
    void query(position pos, float r, F&& f) const {
        for (int cx = idx(pos.x - r); cx <= idx(pos.x + r); ++cx)
            for (int cy = idx(pos.y - r); cy <= idx(pos.y + r); ++cy)
                if (auto it = cells.find(key(cx, cy)); it != cells.end())
                    for (auto e : it->second) f(e);
    }
};

struct Grids {
    SpatialGrid grid0;
    SpatialGrid grid1;
    SpatialGrid& get_allies(side myside)  {return myside==SIDE0 ? grid0 : grid1;};
    SpatialGrid& get_enemies(side myside) {return myside==SIDE0 ? grid1 : grid0;};
};

void create_grids(entt::registry &registry);
void update_grids(entt::registry &registry);

#endif