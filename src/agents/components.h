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

#endif