#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "xwing.h"

/**
 * Bounding box definition
 */
typedef struct {
    double min_x;
    double max_x;
    double min_y;
    double max_y;
    double min_z;
    double max_z;
} Bounding_Box;

/**
 * Finds a "box shaped" bounding for the model and returns with it
 */
Bounding_Box get_bounding_box(Object* object);

/**
 * Checks if two bounding box is colliding
 */
bool is_collide(Bounding_Box bound1, Bounding_Box bound2);

/**
 * Checks if a point is in the bounding box
 */
bool collision_test(Bounding_Box bound, double x, double y, double z);

#endif /* BOUNDING_BOX_H */