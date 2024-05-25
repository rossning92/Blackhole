/**
 * @file render.h
 * @author Ross Ning (rossning92@gmail.com)
 * @brief Utility functions for GL shader.
 * @version 0.1
 * @date 2020-08-29
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

GLuint createShaderProgram(const std::string &vertexShaderFile,
                           const std::string &fragmentShaderFile);

#endif /* SHADER_H */
