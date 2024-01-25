#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <GLFW/glfw3.h>

#include "camera.h"

class Screen_Size
{
public:
    unsigned int width;
    unsigned int height;
    Screen_Size(unsigned int screen_width, unsigned int screen_height)
        : width(screen_width), height(screen_height){};
    Screen_Size(){};
};

class Screen
{
public:
    Screen(int screen_width, int screen_height)
    {
        size.width = screen_width;
        size.height = screen_height;
        aspect_ratio = (float)size.width / (float)size.height;

        lastX = (float)size.width / 2.0f;
        lastY = (float)size.height / 2.0f;
        is_first_mouse = true;

        last_time = 0.0f;
    };
    Camera *getCamera() { return &camera; }

    void resize(int width, int height);
    void createWindow();
    void processInput();

    // window
    Screen_Size size;
    float aspect_ratio;
    GLFWwindow *window;

    // camera
    Camera camera;
    float lastX;
    float lastY;
    bool is_first_mouse;

    // timing
    float last_time;
};


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif