#ifndef OBJECT_LOGIC_H
#define OBJECT_LOGIC_H

#include "utils.h"
#include "camera.h"
#include "texture.h"
#include <stdbool.h>
#include <obj/model.h>

/**
 * Object definition (a model that has a position, rotation and can be speed applied)
 */
typedef struct {
    Model model;
    vec3 position;
    vec3 rotation;
    vec3 speed;
    int texture;
} Object;

/**
 * Laser definition (a laser, which will be fired from the xwing. Has a position, rotation and able to check that it is on the screen or not)
 */
typedef struct {
    Model model;
    vec3 position;
    vec3 start_position;
    vec3 rotation;
    int texture;
    bool is_alive;
} Laser;

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

/*
* Represents which weapon will be the next to fire. it is clamped between 1 and 4
*/
int weapon_rotation;

/*
* Represents how far the laser can travel
*/
double laser_travel_distance;

/**
 * Initialize the object to the start position.
 */
void init_object(Object* object, vec3 position, vec3 rotation);

/**
 * Update the position of the object.
 */
void update_object(Object* object, double time);

/**
 * Set the horizontal and vertical rotation of the object.
 */
void rotate_object(Object* object, double horizontal, double vertical);

/**
 * Set the speed of forward and backward motion.
 */
void set_object_speed(Object* object, double speed);

/**
 * Set the speed of left and right side steps.
 */
void set_object_side_speed(Object* object, double speed);

/**
 * Set the speed of up and down side steps.
 */
void set_object_vertical_speed(Object* object, double speed);

/**
 * Follows the selected object nad add an offset to the camera
 */
void follow_object(Camera* camera, Object* object);

/**
 * Updates the position of the geostationary object.
 */
void update_Geostac_Loc(Object* object, double distance);

/**
 * Shoots a laser from one of the Xwing's cannons. After that it rotates to the next cannon.
 */
void shoot(Object* xwing, Laser lasers[4]);

/**
 * Updates the four cannons emitted laser position, and aftera distance it destroys it.
 */
void update_lasers(Laser lasers[4], double time);

/**
 * Finds a "box shaped" bounding for the model and returns with it
 */
Bounding_Box get_bounding_box(Model* model, vec3* position);

/**
 * Checks if two bounding box is colliding
 */
bool is_collide(Bounding_Box bound1, Bounding_Box bound2);

/**
 * Checks if a point is in the bounding box
 */
bool collision_test(Bounding_Box bound, double x, double y, double z);

/**
 * Sets a new random position and random rotation of the given object relative to the xwing/ given object
 */
void setNewRandPosAndRot(Object* object, Object* xwing, int distance);

#endif /* OBJECT_LOGIC_H */
