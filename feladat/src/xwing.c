#include "xwing.h"

#include <GL/glut.h>
#include <math.h>
#include <time.h>

void init_object(Object* object, vec3 position, vec3 rotation)
{
    object->position.x = position.x;
    object->position.y = position.y;
    object->position.z = position.z;
    object->rotation.x = rotation.x;
    object->rotation.y = rotation.y;
    object->rotation.z = rotation.z;
    object->speed.x = 0.0;
    object->speed.y = 0.0;
    object->speed.z = 0.0;
}

void update_object(Object* object, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(object->rotation.z);
    side_angle = degree_to_radian(object->rotation.z + 90.0);
    
    object->position.x += cos(angle) * object->speed.y * time;
    object->position.y += sin(angle) * object->speed.y * time;
    object->position.x += cos(side_angle) * object->speed.x * time;
    object->position.y += sin(side_angle) * object->speed.x * time;

    object->position.z += object->speed.z * time;
}

void rotate_object(Object* object, double horizontal, double vertical)
{
    object->rotation.z += horizontal;
    object->rotation.x += vertical;

    if (object->rotation.z < 0) {
        object->rotation.z += 360.0;
    }

    if (object->rotation.z > 360.0) {
        object->rotation.z -= 360.0;
    }

    if (object->rotation.x < 0) {
        object->rotation.x += 360.0;
    }

    if (object->rotation.x > 360.0) {
        object->rotation.x -= 360.0;
    }
}

void set_object_speed(Object* object, double speed)
{
    object->speed.x = speed;
}

void set_object_side_speed(Object* object, double speed)
{
    object->speed.y = speed;
}

void set_object_vertical_speed(Object* object, double speed)
{
    object->speed.z = speed;
}

void follow_object(Camera* camera, Object* object) {
    double side_angle;
    side_angle = degree_to_radian(object->rotation.z + 90.0);

    camera->position = object->position;
    camera->rotation.x = object->rotation.x;
    camera->rotation.y = object->rotation.y;
    camera->rotation.z = object->rotation.z;

    /*offset of the camera*/
    camera->position.x += cos(side_angle) * -6;
    camera->position.y += sin(side_angle) * -6;
    camera->position.z += 2;
}
