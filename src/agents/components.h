#ifndef AGENTS_COMP_H
#define AGENTS_COMP_H

struct position
{
    float x, y;
};

struct velocity
{
    float x, y;
};

struct orientation
{
    float rad;
};

struct size
{
    float size;
};

enum side
{
    SIDE0,
    SIDE1
};

struct perception
{
    float allies_perception_radius;
    float enemies_perception_radius;
    // should be larger or equal to enemies_perception_radius
    float closest_enemy_search_radius;
};

enum status
{
    FINE, DISABLED, PANICKED, RETREATING
};

#endif