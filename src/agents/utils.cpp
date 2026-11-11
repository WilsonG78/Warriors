#include <cmath>

#include <agents/components.h>

float distance_pos(position pos1, position pos2)
{
    float t1 = pos1.x - pos2.x;
    float t2 = pos1.y - pos2.y;
    return sqrtf(t1*t1 + t2*t2);
}

float direction_pos(position pos1, position pos2)
{
    float x = pos2.x - pos1.x;
    float y = pos2.y - pos1.y;
    return atan2f(y, x);
}