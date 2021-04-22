#include "callbacks.h"
#include "camera.h"
#include "xwing.h"
#include <ctype.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*glPushMatrix();*/
    set_view(&camera);
    draw_scene(&scene);
    /*glPopMatrix();*/

    if (is_help_visible) {
        show_help();
    }
    else
    {
        show_HUD();
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    if (state == 0 && scene.isPaused) {
        mouse_position.x = x;
        mouse_position.y = y;
    }
    else if (state == 0) {
        shoot(&scene.xwing.object, scene.laserbeam_dummy, &scene.head);
    }
    else {
        /*dummies*/
        button = button;
        state = state;
    }
}

void motion(int x, int y)
{
    if (scene.isPaused) {
        rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
        mouse_position.x = x;
        mouse_position.y = y;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (tolower(key)) {
    case 'w':
        if (!scene.isPaused) {
            set_object_speed(&(scene.xwing.object), 30);
        }
        else {
            set_camera_speed(&camera, 1);
        }
        break;
    case 's':
        if (!scene.isPaused){
            set_object_speed(&(scene.xwing.object), -5);
        }
        else {
            set_camera_speed(&camera, -1);
        }
        break;
    case 'a':
        if (!scene.isPaused){
            rotate_object(&(scene.xwing.object), 1, 0); 
            follow_object(&camera, &(scene.xwing.object));
        }
        else {
            set_camera_side_speed(&camera, 1);
        } 
        break;
    case 'd':
        if (!scene.isPaused) {
            rotate_object(&(scene.xwing.object), -1, 0); 
            follow_object(&camera, &(scene.xwing.object));
        }
        else {
            set_camera_side_speed(&camera, -1);
        }
        break;
    case 'q':
        if (!scene.isPaused) {
            set_object_vertical_speed(&(scene.xwing.object), -10);
        }
        else {
            set_camera_vertical_speed(&camera, -1);
        }
        break;
    case 'e':
        if (!scene.isPaused) {
            set_object_vertical_speed(&(scene.xwing.object), 10);
        }
        else {
            set_camera_vertical_speed(&camera, 1);
        }
        break;
    case 'p':
        if (scene.isPaused)
            scene.isPaused = FALSE;
        else
            scene.isPaused = TRUE;
        break;
    case 't':
        if (is_help_visible) {
            is_help_visible = FALSE;
        }
        else {
            is_help_visible = TRUE;
        }
        break;
    case 'o':
        if (scene.origin) {
            scene.origin = FALSE;
        }
        else {
            scene.origin = TRUE;
        }
        break;
    case '+':
        if (scene.lightIntensity < 1.0)
            scene.lightIntensity += 0.02;
        break;
    case '-':
        if (scene.lightIntensity > 0)
            scene.lightIntensity -= 0.02;
        break;
    case '*':
        if (scene.fogIntensity < 1.0)
            scene.fogIntensity += 0.00005f;
        break;
    case '/':
        if (scene.fogIntensity > 0)
            scene.fogIntensity -= 0.00005f;
        break;
        /*dummies*/
        x = x;
        y = y;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (tolower(key)) {
    case 'w':
    case 's':
        if (!scene.isPaused) {
            set_object_speed(&(scene.xwing.object), 0.0);
        }
        else {
            set_camera_speed(&camera, 0.0);            
        }
        break;
    case 'a':
    case 'd':
        if (!scene.isPaused) {

        }
        else {
            set_camera_side_speed(&camera, 0.0);
        }
        break;
    case 'q':
    case 'e':
        if (!scene.isPaused) {
            set_object_vertical_speed(&(scene.xwing.object), 0);
        }
        else {
            set_camera_vertical_speed(&camera, 0.0);
        }
        break;
        /*dummies*/
        x = x;
        y = y;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    if (scene.isPaused)
    {
        update_camera(&camera, elapsed_time);
    }
    else
    {
        update_object(&(scene.xwing.object), elapsed_time);
        follow_object(&camera, &(scene.xwing.object));
    }

    update_laserbeams(&scene.head, elapsed_time);

    rotate_object(&(scene.geostatObj.object), 0.006, 0);
    update_Geostac_Loc(&(scene.geostatObj.object), 800);
    
    glutPostRedisplay();
}
