#ifndef SKYBOX_H
#define SKYBOX_H

#include <stdio.h> 
#include "scene.h"

enum { SKY_LEFT = 0, SKY_BACK, SKY_RIGHT, SKY_FRONT, SKY_TOP, SKY_BOTTOM };      /*constants for the skybox faces, so don't have to remember the numbers*/
unsigned int skybox[6]; /*the ids for the textures*/

void initskybox();

void killskybox();

void drawSkybox(Scene* scene, double size);

#endif /* SKYBOX_H */