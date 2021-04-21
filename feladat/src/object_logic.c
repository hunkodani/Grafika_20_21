#include "object_logic.h"

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

void shoot(Object* xwing, Laser lasers[4]) {
    double angle, side_angle;
    if (!(lasers[weapon_rotation - 1].is_alive))
    {        
        angle = degree_to_radian(xwing->rotation.z);
        side_angle = degree_to_radian(xwing->rotation.z + 90.0);

        lasers[weapon_rotation - 1].position.x = xwing->position.x + cos(side_angle) * 0.5;
        lasers[weapon_rotation - 1].position.y = xwing->position.y + sin(side_angle) * 0.5;

        if (weapon_rotation == 1 || weapon_rotation == 3)
        {
            lasers[weapon_rotation - 1].position.x += cos(angle) * 1.44;
            lasers[weapon_rotation - 1].position.y += sin(angle) * 1.44;
        }
        else
        {
            lasers[weapon_rotation - 1].position.x += cos(angle) * -1.44;
            lasers[weapon_rotation - 1].position.y += sin(angle) * -1.44;
        }

        if (weapon_rotation == 3 || weapon_rotation == 4)
        {
            lasers[weapon_rotation - 1].position.z = xwing->position.z + 0.17;
        }
        else
        {
            lasers[weapon_rotation - 1].position.z = xwing->position.z + 0.39;
        }

        lasers[weapon_rotation - 1].start_position = lasers[weapon_rotation - 1].position;
        lasers[weapon_rotation - 1].rotation.z = xwing->rotation.z;
        lasers[weapon_rotation - 1].is_alive = TRUE;

        if (weapon_rotation % 4 != 0)
        {
            weapon_rotation++;
        }
        else if (!(lasers[0].is_alive))
        {
            weapon_rotation = 1;
        }

    }
}

void update_lasers(Laser lasers[4], double time) {
    int i;
    double speed;
    double side_angle;
    speed = 50;
    for (i = 0; i < 4; i++)
    {
        if (lasers[i].is_alive)
        {
            side_angle = degree_to_radian(lasers[i].rotation.z + 90.0);

            lasers[i].position.x += cos(side_angle) * speed * time;
            lasers[i].position.y += sin(side_angle) * speed * time;
            
            if (sqrt(abs(pow((lasers[i].position.x - lasers[i].start_position.x), 2) + pow((lasers[i].position.y - lasers[i].start_position.y), 2))) >= laser_travel_distance)
            {
                lasers[i].is_alive = FALSE;
            }
        }      
    }
}

Bounding_Box get_bounding_box(Model* model, vec3* position)
{
    int i;
    double x, y, z;
    Bounding_Box bounding;

    if (model->n_vertices == 0) {
        return bounding;
    }

    bounding.min_x = model->vertices[0].x;
    bounding.max_x = model->vertices[0].x;
    bounding.min_y = model->vertices[0].y;
    bounding.max_y = model->vertices[0].y;
    bounding.min_z = model->vertices[0].z;
    bounding.max_z = model->vertices[0].z;

    for (i = 0; i < model->n_vertices; ++i) {
        x = model->vertices[i].x;
        y = model->vertices[i].y;
        z = model->vertices[i].z;
        if (x < bounding.min_x) {
            bounding.min_x = x;
        }
        else if (x > bounding.max_x) {
            bounding.max_x = x;
        }
        if (y < bounding.min_y) {
            bounding.min_y = y;
        }
        else if (y > bounding.max_y) {
            bounding.max_y = y;
        }
        if (z < bounding.min_z) {
            bounding.min_z = z;
        }
        else if (z > bounding.max_z) {
            bounding.max_z = z;
        }
    }

    bounding.min_x = position->x + bounding.min_x;
    bounding.max_x = position->x + bounding.max_x;
    bounding.min_y = position->y + bounding.min_y;
    bounding.max_y = position->y + bounding.max_y;
    bounding.min_z = position->z + bounding.min_z;
    bounding.max_z = position->z + bounding.max_z;

    return bounding;
}

bool is_collide(Bounding_Box bound1, Bounding_Box bound2) {

    /*For the debug of the collision*/
    /*glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glVertex3f(bound1.min_x, bound1.min_y, bound1.min_z);
    glVertex3f(bound1.min_x, bound1.min_y, bound1.max_z);
    glVertex3f(bound1.min_x, bound1.max_y, bound1.min_z);
    glVertex3f(bound1.min_x, bound1.max_y, bound1.max_z);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(bound1.max_x, bound1.min_y, bound1.min_z);
    glVertex3f(bound1.max_x, bound1.min_y, bound1.max_z);
    glVertex3f(bound1.max_x, bound1.max_y, bound1.min_z);
    glVertex3f(bound1.max_x, bound1.max_y, bound1.max_z);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(bound1.min_x, bound1.min_y, bound1.min_z);
    glVertex3f(bound1.min_x, bound1.min_y, bound1.max_z);
    glVertex3f(bound1.max_x, bound1.min_y, bound1.min_z);
    glVertex3f(bound1.max_x, bound1.min_y, bound1.max_z);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(bound1.min_x, bound1.max_y, bound1.min_z);
    glVertex3f(bound1.min_x, bound1.max_y, bound1.max_z);
    glVertex3f(bound1.max_x, bound1.max_y, bound1.min_z);
    glVertex3f(bound1.max_x, bound1.max_y, bound1.max_z);
    glEnd();
    glEnable(GL_LIGHTING);*/

    /*Check every point of the box (8 point)*/
    if (collision_test(bound1, bound2.min_x, bound2.min_y, bound2.min_z))
    {
        return TRUE;
    }
    else if (collision_test(bound1, bound2.min_x, bound2.min_y, bound2.max_z))
    {
        return TRUE;
    }
    else if (collision_test(bound1, bound2.min_x, bound2.max_y, bound2.min_z))
    {
        return TRUE;
    }
    else if (collision_test(bound1, bound2.min_x, bound2.max_y, bound2.max_z))
    {
        return TRUE;
    }
    else if (collision_test(bound1, bound2.max_x, bound2.min_y, bound2.min_z))
    {
        return TRUE;
    }
    else if (collision_test(bound1, bound2.max_x, bound2.min_y, bound2.max_z))
    {
        return TRUE;
    }
    else if (collision_test(bound1, bound2.max_x, bound2.max_y, bound2.min_z))
    {
        return TRUE;
    }
    else if (collision_test(bound1, bound2.max_x, bound2.max_y, bound2.max_z))
    {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

bool collision_test(Bounding_Box bound, double x, double y, double z) {
    if (bound.min_x <= x && x <= bound.max_x && bound.min_y <= y && y <= bound.max_y && bound.min_z <= z && z <= bound.max_z) {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void setNewRandPosAndRot(Object* object, Object* xwing, int distance) {
    int value;

    object->position = xwing->position;

    if ((value = rand() % 101 - 50) < 0)
    {
        object->position.x = value - distance;
    }
    else
    {
        object->position.x = value + distance;
    }

    if ((value = rand() % 101 - 50) < 0)
    {
        object->position.y = value - distance;
    }
    else
    {
        object->position.y = value + distance;
    }

    object->position.z = rand() % 11 - 5;

    object->rotation.z = rand() % 360;
}
