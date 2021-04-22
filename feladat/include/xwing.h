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

typedef struct {
    Object object;
} Xwing;

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

#endif /* OBJECT_LOGIC_H */
