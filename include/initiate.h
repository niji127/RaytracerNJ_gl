#ifndef INITIATE_H
#define INITIATE_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void initiate_glfw(int major_version, int minor_version, int msaa_samples);
void initiate_glad();

#endif