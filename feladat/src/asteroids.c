#include "asteroids.h"
#include <math.h>

void update_Geostac_Loc(Object* object, double distance) {
    double angle;
    double side_angle;

    angle = degree_to_radian(object->rotation.z);
    side_angle = degree_to_radian(object->rotation.z + 90.0);

    object->position.x = cos(angle) * distance;
    object->position.y = sin(angle) * distance;
    object->position.x = cos(side_angle) * distance;
    object->position.y = sin(side_angle) * distance;

    object->position.z = sin(angle) * 15;
}
