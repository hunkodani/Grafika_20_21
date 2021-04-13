#include "skybox.h"
#include "texture.h"

#include <SOIL/SOIL.h>
#include <GL/glut.h>

void initskybox()
{
    skybox[SKY_LEFT] = load_texture("resources/textures/bluecloud_lf.jpg");
    skybox[SKY_BACK] = load_texture("resources/textures/bluecloud_bk.jpg");
    skybox[SKY_RIGHT] = load_texture("resources/textures/bluecloud_rt.jpg");
    skybox[SKY_FRONT] = load_texture("resources/textures/bluecloud_ft.jpg");
    skybox[SKY_TOP] = load_texture("resources/textures/bluecloud_up.jpg");
    skybox[SKY_BOTTOM] = load_texture("resources/textures/bluecloud_dn.jpg");
}

/*delete all of the textures from the skybox array (to avoid memory leaks)*/
void killskybox()
{
    glDeleteTextures(6, &skybox[0]);
}

void drawSkybox(Scene* scene, double size)
{
    /*turn off lighting, depth testing
    and turn on texturing
    if the depth test is disabled then it will be transparent to other materials, and can be seen through everything*/
    glDisable(GL_LIGHTING);
    /*glDisable(GL_DEPTH_TEST);*/
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(scene->lightIntensity + 0.2, scene->lightIntensity + 0.2, scene->lightIntensity + 0.2); /*The 0.2 is the offset. it does not matter if it is over 1.0 because it is clamped -->always between 0 and 1*/

    /*top face*/
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_TOP]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);                     /*the texture coordinates may vary in different textures*/
    glVertex3f(size / 2, size / 2, size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-size / 2, size / 2, size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size / 2, -size / 2, size / 2);
    glEnd();
    /*right face*/
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_RIGHT]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-size / 2, size / 2, size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glEnd();
    /*bottom face*/
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_BOTTOM]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size / 2, size / 2, -size / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glEnd();
    /*left face*/
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_LEFT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(size / 2, size / 2, -size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size / 2, size / 2, size / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size / 2, -size / 2, size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glEnd();
    /*front face*/
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_FRONT]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(size / 2, size / 2, size / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size / 2, size / 2, size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(size / 2, size / 2, -size / 2);
    glEnd();
    /*back face*/
    glBindTexture(GL_TEXTURE_2D, skybox[SKY_BACK]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size / 2, -size / 2, size / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glEnd();

    /*turn back what has been disabled*/
    glEnable(GL_LIGHTING);
    /*glEnable(GL_DEPTH_TEST);*/
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
}