#include <entt/entt.hpp>

/**
 * @brief component defining relation between soldier and commander
 * this component can be added to a soldier to assign him under commander
 */
struct relationToCommander
{
    entt::entity parent;
};