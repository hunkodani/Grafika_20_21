#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "porsche.obj");
    scene->texture_id = load_texture("cube.png"); 

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 0.2;
    scene->material.ambient.green = 0.2;
    scene->material.ambient.blue = 0.1;

    scene->material.diffuse.red = 0.8;
    scene->material.diffuse.green = 0.9;
    scene->material.diffuse.blue = 0.5;

    scene->material.specular.red = 0.4;
    scene->material.specular.green = 0.6;
    scene->material.specular.blue = 0.5;

    scene->material.shininess = 40.0;

    //Red rubber
    scene->red_material.ambient.red = 0.05f;
    scene->red_material.ambient.green = 0.0;
    scene->red_material.ambient.blue = 0.0;

    scene->red_material.diffuse.red = 0.5f;
    scene->red_material.diffuse.green = 0.4f;
    scene->red_material.diffuse.blue = 0.4f;

    scene->red_material.specular.red = 0.7f;
    scene->red_material.specular.green = 0.04f;
    scene->red_material.specular.blue = 0.04f;

    scene->red_material.shininess = 10.0f;

    //Green emerald
    scene->green_material.ambient.red = 0.0215f;
    scene->green_material.ambient.green = 0.1745f;
    scene->green_material.ambient.blue = 0.0215f;

    scene->green_material.diffuse.red = 0.07568f;
    scene->green_material.diffuse.green = 0.61424f;
    scene->green_material.diffuse.blue = 0.07568f;

    scene->green_material.specular.red = 0.633f;
    scene->green_material.specular.green = 0.727811f;
    scene->green_material.specular.blue = 0.633f;

    scene->green_material.shininess = 76.8f;
}

void set_lighting()
{
    float ambient_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene)
{
    /*set_material(&(scene->material));*/
    set_lighting();
    draw_origin();

    set_material(&(scene->material));
    glPushMatrix();
    glTranslatef(0, 0, -10);
    glutSolidSphere(1,30,30);
    /*draw_model(&(scene->cube));*/
    glPopMatrix();

    set_material(&(scene->red_material));
    glPushMatrix();
    glRotatef(90,1,0,0);
    draw_model(&(scene->cube));
    glPopMatrix();

    set_material(&(scene->green_material));
    glPushMatrix();
    glTranslatef(4,0,0);
    glRotatef(90, 1, 0, 0);
    draw_model(&(scene->cube));
    glPopMatrix();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
