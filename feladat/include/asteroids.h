#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "xwing.h"

typedef struct {
	Object object;
} Asteroids;

/**
 * Updates the position of the geostationary object.
 */
void update_Geostac_Loc(Object* object, double distance);

#endif /* ASTEROIDS_H */