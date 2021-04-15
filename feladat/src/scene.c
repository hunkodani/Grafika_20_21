#include "scene.h"
#include "skybox.h"

#include <GL/glut.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <obj/transform.h>
#include <time.h>

void init_scene(Scene* scene)
{
    srand(time(0));
    glEnable(GL_FOG);
    scene = scene;
    scene->lightIntensity = 1.0;
    scene->fogIntensity = 0.0;
    weapon_rotation = 1;
    laser_travel_distance = 100;

    /*xwing loading*/
    load_model(&scene->xwing.model, "resources/models/x-wing.obj");
    strcpy(scene->xwing.name, "xwing");
    scale_model(&scene->xwing.model, 0.25f, 0.25f, 0.25f);
    scene->xwing.texture = load_texture("resources/textures/Xwing_Albedo.png");

    /*lasers loading*/
    load_model(&scene->lasers[0].model, "resources/models/laser.obj");
    scale_model(&scene->lasers[0].model, 0.25f, 0.25f, 0.25f);
    scene->lasers[1].model = scene->lasers[0].model;
    scene->lasers[2].model = scene->lasers[0].model;
    scene->lasers[3].model = scene->lasers[0].model;
    scene->lasers[0].texture = load_texture("resources/textures/laser_Albedo.png");
    scene->lasers[1].texture = scene->lasers[0].texture;
    scene->lasers[2].texture = scene->lasers[0].texture;
    scene->lasers[3].texture = scene->lasers[0].texture;

    /*destinations loading*/
    load_model(&scene->dest_point[0].model, "resources/models/destination.obj");
    scene->dest_point[1].model = scene->dest_point[0].model;
    scene->dest_point[0].texture = load_texture("resources/textures/destination_Albedo.png");
    scene->dest_point[1].texture = scene->dest_point[0].texture;
    setNewRandPosAndRot(&scene->dest_point[0], &scene->xwing, 60);
    setNewRandPosAndRot(&scene->dest_point[1], &scene->xwing, 60);

    /*targets loading*/
    load_model(&scene->target[0].model, "resources/models/cube.obj");
    scene->target[1].model = scene->target[0].model;
    scene->target[0].texture = load_texture("resources/textures/cross.png");
    scene->target[1].texture = scene->target[0].texture;
    setNewRandPosAndRot(&scene->target[0], &scene->xwing, 50);
    setNewRandPosAndRot(&scene->target[1], &scene->xwing, 50);

    /*asteroid loading*/
    load_model(&scene->geostatObj.model, "resources/models/rocks.obj");
    scene->geostatObj.texture = load_texture("resources/textures/Rocks_Albedo.png");
    /*glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 0.2;
    scene->material.ambient.green = 0.2;
    scene->material.ambient.blue = 0.1;

    scene->material.diffuse.red = 0.8;
    scene->material.diffuse.green = 0.9;
    scene->material.diffuse.blue = 0.5;

    scene->material.specular.red = 0.4;
    scene->material.specular.green = 0.6;
    scene->material.specular.blue = 0.5;

    scene->material.shininess = 40.0;*/

}

void set_lighting(Scene* scene)
{
    float ambient_light[4]; 
    float diffuse_light[4];
    float specular_light[4];
    float position[4];
    ambient_light[0] = scene->lightIntensity * 0.35;
    ambient_light[1] = scene->lightIntensity * 0.35;
    ambient_light[2] = scene->lightIntensity * 0.35;
    ambient_light[3] = 1.0f;
    
    diffuse_light[0] = scene->lightIntensity;
    diffuse_light[1] = scene->lightIntensity;
    diffuse_light[2] = scene->lightIntensity;
    diffuse_light[3] = 1.0f;
    
    specular_light[0] = scene->lightIntensity;
    specular_light[1] = scene->lightIntensity;
    specular_light[2] = scene->lightIntensity;
    specular_light[3] = 1.0f;

    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 10.0f;
    position[3] = 0.0f;

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[4];
    float diffuse_material_color[4];
    float specular_material_color[4];

    ambient_material_color[0] = material->ambient.red;
    ambient_material_color[1] = material->ambient.green;
    ambient_material_color[2] = material->ambient.blue;

    diffuse_material_color[0] = material->diffuse.red;
    diffuse_material_color[1] = material->diffuse.green;
    diffuse_material_color[2] = material->diffuse.blue;

    specular_material_color[0] = material->specular.red;
    specular_material_color[1] = material->specular.green;
    specular_material_color[2] = material->specular.blue;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(Scene* scene)
{
    int i, j;

    drawSkybox(scene, 3500.0f);
    set_lighting(scene);
    fog(scene);
    if (scene->origin) {
        draw_origin();
    }
    glEnable(GL_TEXTURE_2D);

    glPushMatrix(); 
        glBindTexture(GL_TEXTURE_2D, scene->xwing.texture);
        glTranslatef(scene->xwing.position.x, scene->xwing.position.y, scene->xwing.position.z);
        glRotatef(scene->xwing.rotation.z, 0.0f, 0.0f, 1.0f);
        draw_model(&(scene->xwing.model));
    glPopMatrix();

    for (j = 0; j < 2; j++)
    {
        /*needs to check if first collide to second or second collide to first (the second may contain the first, so first is not "collide with the second, because the points is outside")*/
        if (is_collide(get_bounding_box(&scene->xwing.model, &scene->xwing.position), get_bounding_box(&scene->dest_point[j].model, &scene->dest_point[j].position))
            || is_collide(get_bounding_box(&scene->dest_point[j].model, &scene->dest_point[j].position), get_bounding_box(&scene->xwing.model, &scene->xwing.position))
            )
        {
            dest_counter++;
            setNewRandPosAndRot(&scene->dest_point[j], &scene->xwing, 50);
        }
    }

    for (i = 0; i < 2; i++)
    {
        
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, scene->dest_point[i].texture);
            glTranslatef(scene->dest_point[i].position.x, scene->dest_point[i].position.y, scene->dest_point[i].position.z);
            glRotatef(scene->dest_point[i].rotation.z, 0.0f, 0.0f, 1.0f);
            draw_model(&(scene->dest_point[i].model));
        glPopMatrix();
    }

    for (i = 0; i < 2; i++)
    {
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, scene->target[i].texture);
            glTranslatef(scene->target[i].position.x, scene->target[i].position.y, scene->target[i].position.z);
            glRotatef(scene->target[i].rotation.z, 0.0f, 0.0f, 1.0f);
            draw_model(&(scene->target[i].model));
        glPopMatrix();
    }
    
    for (i = 0; i < 4; i++)
    {
        if (scene->lasers[i].is_alive) {
            for (j = 0; j < 2; j++)
            {
                /*needs to check if first collide to second or second collide to first (the second may contain the first, so first is not "collide with the second, because the points is outside")*/
                if (is_collide(get_bounding_box(&scene->lasers[i].model, &scene->lasers[i].position), get_bounding_box(&scene->target[j].model, &scene->target[j].position))
                    || is_collide(get_bounding_box(&scene->target[j].model, &scene->target[j].position), get_bounding_box(&scene->lasers[i].model, &scene->lasers[i].position))
                    ) 
                {
                    scene->lasers[i].is_alive = FALSE;
                    target_counter++;
                    setNewRandPosAndRot(&scene->target[j], &scene->xwing, 50);
                }
            }
        }
        if (scene->lasers[i].is_alive)
        {
            glBindTexture(GL_TEXTURE_2D, scene->lasers[i].texture);
            glPushMatrix();
                glTranslatef(scene->lasers[i].position.x, scene->lasers[i].position.y, scene->lasers[i].position.z);
                glRotatef(scene->lasers[i].rotation.z, 0.0f, 0.0f, 1.0f);
                draw_model(&(scene->lasers[i].model));
            glPopMatrix();
        }        
    }            

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->geostatObj.texture);
        glTranslatef(scene->geostatObj.position.x, scene->geostatObj.position.y, scene->geostatObj.position.z);
        glRotatef(scene->geostatObj.rotation.z, 0.0f, 0.0f, 1.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        draw_model(&(scene->geostatObj.model));
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void draw_origin()
{
    glEnable(GL_COLOR_MATERIAL);
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
    glColor3f(1, 1, 1);
    glDisable(GL_COLOR_MATERIAL);
}

void fog(Scene* scene) {
    GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f, 1 };
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_START, -10.0f);
    glFogf(GL_FOG_END, 100.0f);
    glFogf(GL_FOG_DENSITY, scene->fogIntensity);
}

void textDrawToWorld(float x, float y, float z, void* font, char* string, Color color)
{
    int len, i;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(color.red, color.green, color.blue);
    glRasterPos3f(x, y, z);
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
