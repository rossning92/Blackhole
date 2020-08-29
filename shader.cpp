#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>

static std::string readFile(const std::string &file) {
  std::string VertexShaderCode;
  std::ifstream ifs(file, std::ios::in);
  if (ifs.is_open()) {
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
  } else {
    throw "Failed to open file: " + file;
  }
}

static GLuint compileShader(const std::string &shaderSource,
                            GLenum shaderType) {
  // Create shader
  GLuint shader = glCreateShader(shaderType);

  // Compile shader
  char const *pShaderSource = shaderSource.c_str();
  glShaderSource(shader, 1, &pShaderSource, nullptr);
  glCompileShader(shader);

  GLint success = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {

    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
    std::cout << infoLog[0] << std::endl;
    glDeleteShader(shader);
    throw "Failed to compile the shader.";
  }

  return shader;
}

GLuint createShaderProgram(const std::string &vertexShaderFile,
                           const std::string &fragmentShaderFile) {

  // Compile vertex and fragment shaders.
  std::cout << "Compiling vertex shader: " << vertexShaderFile << std::endl;
  GLuint vertexShader =
      compileShader(readFile(vertexShaderFile), GL_VERTEX_SHADER);

  std::cout << "Compiling fragment shader: " << fragmentShaderFile << std::endl;
  GLuint fragmentShader =
      compileShader(readFile(fragmentShaderFile), GL_FRAGMENT_SHADER);

  // Create shader program.
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Link the program.
  glLinkProgram(program);
  GLint isLinked = GL_FALSE;
  glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE) {
    int maxLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    if (maxLength > 0) {
      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program, maxLength, NULL, &infoLog[0]);
      std::cout << infoLog[0] << std::endl;
      throw "Failed to link the shader.";
    }
  }

  // Detach shaders after a successful link.
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}