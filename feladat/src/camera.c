#include "camera.h"

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "scene.h"
#include "callbacks.h"

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    is_help_visible = FALSE;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;

    camera->position.z += camera->speed.z * time;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.y = -speed;
}

void set_camera_vertical_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}

void show_help()
{
    int i;
    float y;
    Color color;
    char str[18][100] = {
        "Iranyitas:", 
        "   Hajo:",
        "       W, A, S, D -> iranyitas (elore, hatra, balrafordulas, jobbrafordulas)",
        "       Q, E -- fel-le mozgas",
        "       Eger Bal gomb -- lezeragyu loves(1 / kattintas, maximum 4)",
        "   Kamera: (pause mod)",
        "       W, A, S, D -> iranyitas (elore, hatra, balra, jobbra)",
        "       Q, E -- fel-le mozgas",
        "       Eger Bal gomb + Eger X tengely -- jobbra - balra forgatas",
        "       Eger Bal gomb + Eger Y tengely -- fel - le forgatas",
        "   Altalanos:",
        "       P -> \"pause mod \", azaz a kamerával spectator módban lehet mozogni",
        "       T -> helpbar",
        "       O -> origo megjelenitese, elrejtese",
        "       + -> feny novelese",
        "       - -> feny csokkentese",
        "       / -> kod mertekenek novelese",
        "       * -> kod mertekenek csokkentese"
    };
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.25, 1, -2);
    glTexCoord2f(1, 0);
    glVertex3f(1.25, 1, -2);
    glTexCoord2f(1, 1);
    glVertex3f(1.25, -1, -2);
    glTexCoord2f(0, 1);
    glVertex3f(-1.25, -1, -2);
    glEnd();

    y = 0.95f;
    color.red = 1.0;
    color.green = 1.0;
    color.blue = 1.0;

    for (i = 0; i < 18; i++) {
        textDrawToWorld(-1.0f, y, -1.0f, GLUT_BITMAP_9_BY_15, str[i], color);
        y -= 0.05;
    }

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void show_HUD() {
    int i;
    float y;
    char str[2][100];
    Color color;

    sprintf(str[0], "Pontszamok:    celgyurun atrepulve:       %d", dest_counter);
    sprintf(str[1], "               celpontok megsemmisitve:   %d", target_counter);

    y = 0.95f;
    color.red = 0.4;
    color.green = 0.4;
    color.blue = 0.8;

    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    for (i = 0; i < 2; i++) {
        textDrawToWorld(-0.99f, y, -1.0f, GLUT_BITMAP_9_BY_15, str[i], color);
        y -= 0.05;
    }
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}