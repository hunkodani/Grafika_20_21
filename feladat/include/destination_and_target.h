#ifndef DESTINATION_AND_TARGET_H
#define DESTINATION_AND_TARGET_H

#include "xwing.h"

typedef struct {
	Object object;
} Destination;

typedef struct {
	Object object;
} Target;

/**
 * Sets a new random position and random rotation of the given object relative to the xwing/ given object
 */
void setNewRandPosAndRot(Object* object, Object* xwing, int distance);

#endif /* DESTINATION_AND_TARGET_H */