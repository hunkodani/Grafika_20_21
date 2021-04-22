#include "bounding_box.h"

Bounding_Box get_bounding_box(Object* object)
{
    int i;
    double x, y, z;
    Bounding_Box bounding;

    if (object->model.n_vertices == 0) {
        return bounding;
    }

    bounding.min_x = object->model.vertices[0].x;
    bounding.max_x = object->model.vertices[0].x;
    bounding.min_y = object->model.vertices[0].y;
    bounding.max_y = object->model.vertices[0].y;
    bounding.min_z = object->model.vertices[0].z;
    bounding.max_z = object->model.vertices[0].z;

    for (i = 0; i < object->model.n_vertices; ++i) {
        x = object->model.vertices[i].x;
        y = object->model.vertices[i].y;
        z = object->model.vertices[i].z;
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

    bounding.min_x = object->position.x + bounding.min_x;
    bounding.max_x = object->position.x + bounding.max_x;
    bounding.min_y = object->position.y + bounding.min_y;
    bounding.max_y = object->position.y + bounding.max_y;
    bounding.min_z = object->position.z + bounding.min_z;
    bounding.max_z = object->position.z + bounding.max_z;

    return bounding;
}

bool is_collide(Bounding_Box bound1, Bounding_Box bound2) 
{
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
