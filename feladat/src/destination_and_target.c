#include "destination_and_target.h"

void setNewRandPosAndRot(Object* object, Object* xwing, int distance) {
    int value;

    object->position = xwing->position;

    if ((value = rand() % 101 - 50) < 0)
    {
        object->position.x += value - distance;
    }
    else
    {
        object->position.x += value + distance;
    }

    if ((value = rand() % 101 - 50) < 0)
    {
        object->position.y += value - distance;
    }
    else
    {
        object->position.y += value + distance;
    }

    object->position.z = rand() % 11 - 5;

    object->rotation.z = rand() % 360;
}
