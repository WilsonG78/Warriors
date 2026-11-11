#include <entt/entt.hpp>

struct closestEnemy {
    float distance;
    float direction;
};

struct alliesInRadius {
    unsigned int number;
    unsigned int panicked;
    unsigned int disabled;
};

struct enemiesInRadius {
    unsigned int number;
    unsigned int panicked;
    unsigned int disabled;
};

void update_observation_for_soldiers(entt::registry &registry);
