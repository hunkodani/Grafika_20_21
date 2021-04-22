#include "laserbeam.h"
#include <math.h>

void shoot(Object* xwing, Laserbeam laserbeam, LaserNode** head) {
    double angle, side_angle;
    angle = degree_to_radian(xwing->rotation.z);
    side_angle = degree_to_radian(xwing->rotation.z + 90.0);

    laserbeam.object.position.x = xwing->position.x + cos(side_angle) * 0.5;
    laserbeam.object.position.y = xwing->position.y + sin(side_angle) * 0.5;

    if (weapon_rotation == 1 || weapon_rotation == 3)
    {
        laserbeam.object.position.x += cos(angle) * 1.44;
        laserbeam.object.position.y += sin(angle) * 1.44;
    }
    else
    {
        laserbeam.object.position.x += cos(angle) * -1.44;
        laserbeam.object.position.y += sin(angle) * -1.44;
    }

    if (weapon_rotation == 3 || weapon_rotation == 4)
    {
        laserbeam.object.position.z = xwing->position.z + 0.17;
    }
    else
    {
        laserbeam.object.position.z = xwing->position.z + 0.39;
    }

    laserbeam.start_position = laserbeam.object.position;
    laserbeam.object.rotation.z = xwing->rotation.z;
    push_Laserlist(head, laserbeam);

    if (weapon_rotation % 4 != 0)
    {
        weapon_rotation++;
    }
    else
    {
        weapon_rotation = 1;
    }
}

void update_laserbeams(LaserNode** head, double time) {
    double speed;
    double side_angle;
    LaserNode* current = (*head);

    speed = 50;
    while (current != NULL) {
        
        side_angle = degree_to_radian(current->laserbeam.object.rotation.z + 90.0);
        current->laserbeam.object.position.x += cos(side_angle) * speed * time;
        current->laserbeam.object.position.y += sin(side_angle) * speed * time;

        if (sqrt(abs(pow((current->laserbeam.object.position.x - current->laserbeam.start_position.x), 2) + pow((current->laserbeam.object.position.y - current->laserbeam.start_position.y), 2))) >= laser_travel_distance)
        {
            pop_Laserlist(head);
        }
        current = current->next;
    }
}

void push_Laserlist(LaserNode** head, Laserbeam laserbeam) {
    LaserNode* current = (*head);
    if (current != NULL)
    {
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = (LaserNode*)malloc(sizeof(LaserNode));
        current->next->laserbeam = laserbeam;
        current->next->next = NULL;
    }
    else
    {
        (*head) = (LaserNode*)malloc(sizeof(LaserNode));
        (*head)->laserbeam = laserbeam;
        (*head)->next = NULL;
    }
}

void pop_Laserlist(LaserNode** head) {
    LaserNode* next_node = NULL;
    if ((*head)->next != NULL)
    {
        next_node = (*head)->next;
        free(*head);
        *head = next_node;
    }
    else
    {
        free(*head);
        (*head) = NULL;
    }
}

void remove_by_position(LaserNode** head, vec3 position) {
    LaserNode* current = (*head);
    LaserNode* temp_node = NULL;

    if (current->laserbeam.object.position.x == position.x &&
        current->laserbeam.object.position.y == position.y &&
        current->laserbeam.object.position.z == position.z) {
        pop_Laserlist(head);
    }

    while (current->next != NULL) {
        if (current->next->laserbeam.object.position.x == position.x &&
            current->next->laserbeam.object.position.y == position.y &&
            current->next->laserbeam.object.position.z == position.z)
        {
            break;
        }
        current = current->next;
    }

    if (current->next->laserbeam.object.position.x == position.x &&
        current->next->laserbeam.object.position.y == position.y &&
        current->next->laserbeam.object.position.z == position.z)
    {
        if (current->next->next != NULL)
        {
            temp_node = current->next;
            current->next = temp_node->next;
            free(temp_node);
        }
        else
        {
            temp_node = current->next;
            current->next = NULL;
            free(temp_node);
        }
    }
}