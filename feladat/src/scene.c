#include "scene.h"
#include "skybox.h"
#include "bounding_box.h"

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
    scene->head = NULL;

    /*xwing loading*/
    load_model(&scene->xwing.object.model, "resources/models/x-wing.obj");
    scale_model(&scene->xwing.object.model, 0.25f, 0.25f, 0.25f);
    scene->xwing.object.texture = load_texture("resources/textures/Xwing_Albedo.png");

    /*laserbeam dummy loading*/
    load_model(&scene->laserbeam_dummy.object.model, "resources/models/laser.obj");
    scale_model(&scene->laserbeam_dummy.object.model, 0.25f, 0.25f, 0.25f);
    scene->laserbeam_dummy.object.texture = load_texture("resources/textures/laser_Albedo.png");

    /*destinations loading*/
    load_model(&scene->dest_point[0].object.model, "resources/models/destination.obj");
    scene->dest_point[1].object.model = scene->dest_point[0].object.model;
    scene->dest_point[0].object.texture = load_texture("resources/textures/destination_Albedo.png");
    scene->dest_point[1].object.texture = scene->dest_point[0].object.texture;
    setNewRandPosAndRot(&scene->dest_point[0].object, &scene->xwing.object, 60);
    setNewRandPosAndRot(&scene->dest_point[1].object, &scene->xwing.object, 60);

    /*targets loading*/
    load_model(&scene->target[0].object.model, "resources/models/cube.obj");
    scene->target[1].object.model = scene->target[0].object.model;
    scene->target[0].object.texture = load_texture("resources/textures/cross.png");
    scene->target[1].object.texture = scene->target[0].object.texture;
    setNewRandPosAndRot(&scene->target[0].object, &scene->xwing.object, 50);
    setNewRandPosAndRot(&scene->target[1].object, &scene->xwing.object, 50);

    /*asteroid loading*/
    load_model(&scene->geostatObj.object.model, "resources/models/rocks.obj");
    scene->geostatObj.object.texture = load_texture("resources/textures/Rocks_Albedo.png");
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
    LaserNode* current = scene->head;

    drawSkybox(scene, 3500.0f);
    set_lighting(scene);
    fog(scene);
    if (scene->origin) {
        draw_origin();
    }
    glEnable(GL_TEXTURE_2D);

    glPushMatrix(); 
        glBindTexture(GL_TEXTURE_2D, scene->xwing.object.texture);
        glTranslatef(scene->xwing.object.position.x, scene->xwing.object.position.y, scene->xwing.object.position.z);
        glRotatef(scene->xwing.object.rotation.z, 0.0f, 0.0f, 1.0f);
        draw_model(&(scene->xwing.object.model));
    glPopMatrix();

    for (j = 0; j < 2; j++)
    {
        /*needs to check if first collide to second or second collide to first (the second may contain the first, so first is not "collide with the second, because the points is outside")*/
        if (is_collide(get_bounding_box(&scene->xwing.object), get_bounding_box(&scene->dest_point[j].object))
            || is_collide(get_bounding_box(&scene->dest_point[j].object), get_bounding_box(&scene->xwing.object))
            )
        {
            dest_counter++;
            setNewRandPosAndRot(&scene->dest_point[j].object, &scene->xwing.object, 50);
        }
    }

    for (i = 0; i < 2; i++)
    {
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, scene->dest_point[i].object.texture);
            glTranslatef(scene->dest_point[i].object.position.x, scene->dest_point[i].object.position.y, scene->dest_point[i].object.position.z);
            glRotatef(scene->dest_point[i].object.rotation.z, 0.0f, 0.0f, 1.0f);
            draw_model(&(scene->dest_point[i].object.model));
        glPopMatrix();
    }

    for (i = 0; i < 2; i++)
    {
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, scene->target[i].object.texture);
            glTranslatef(scene->target[i].object.position.x, scene->target[i].object.position.y, scene->target[i].object.position.z);
            glRotatef(scene->target[i].object.rotation.z, 0.0f, 0.0f, 1.0f);
            draw_model(&(scene->target[i].object.model));
        glPopMatrix();
    }
    
    while (current != NULL) 
    {
        for (j = 0; j < 2; j++)
        {
            /*needs to check if first collide to second or second collide to first (the second may contain the first, so first is not "collide with the second, because the points is outside")*/
            if (is_collide(get_bounding_box(&current->laserbeam.object), get_bounding_box(&scene->target[j].object))
                || is_collide(get_bounding_box(&scene->target[j].object), get_bounding_box(&current->laserbeam.object))
                )
            {
                target_counter++;
                /*Not working properly*/
                /*remove_by_position(&scene->head, current->laserbeam.object.position);*/
                setNewRandPosAndRot(&scene->target[j].object, &scene->xwing.object, 50);
            }
        }
        glBindTexture(GL_TEXTURE_2D, current->laserbeam.object.texture);
        glPushMatrix();
        glTranslatef(current->laserbeam.object.position.x, current->laserbeam.object.position.y, current->laserbeam.object.position.z);
        glRotatef(current->laserbeam.object.rotation.z, 0.0f, 0.0f, 1.0f);
        draw_model(&(current->laserbeam.object.model));
        glPopMatrix();
        current = current->next;
    }

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->geostatObj.object.texture);
        glTranslatef(scene->geostatObj.object.position.x, scene->geostatObj.object.position.y, scene->geostatObj.object.position.z);
        glRotatef(scene->geostatObj.object.rotation.z, 0.0f, 0.0f, 1.0f);
        draw_model(&(scene->geostatObj.object.model));
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
