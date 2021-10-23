// Header for GLDebugMessageCallback by Plasmoxy 2020
// Feel free to use this in any way.
#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* msg, const void* data);