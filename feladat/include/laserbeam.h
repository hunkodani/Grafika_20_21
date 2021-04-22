#ifndef	LASERBEAM_H
#define LASERBEAM_H

#include "xwing.h"

/**
 * Laserbeam definition (a laser, which will be fired from the xwing. Has a position, rotation and able to check that it is on the screen or not)
 */
typedef struct {
    Object object;
    vec3 start_position;
   /* bool is_alive;*/
} Laserbeam;

typedef struct node {
    Laserbeam laserbeam;
    struct node* next;
} LaserNode;

/*
* Represents which weapon will be the next to fire. it is clamped between 1 and 4
*/
int weapon_rotation;

/*
 * Represents how far the laser can travel
 */
double laser_travel_distance;

/**
 * Shoots a laser from one of the Xwing's cannons. After that it rotates to the next cannon.
 */
void shoot(Object* xwing, Laserbeam laserbeam, LaserNode** head);

/**
 * Updates the four cannons emitted laser position, and aftera distance it destroys it.
 */
void update_laserbeams(LaserNode** head, double time);

/**
 * Linked list functions from https://www.learn-c.org/en/Linked_lists
 * Pushes a laserbeam element to the list
 */
void push_Laserlist(LaserNode** head, Laserbeam laserbeam);

/**
 * Pops the first element from the list
 */
void pop_Laserlist(LaserNode** head);

/**
 * Removes the element, where the element's position is the given
 */
void remove_by_position(LaserNode** head, vec3 position);

#endif /* LASERBEAM_H */