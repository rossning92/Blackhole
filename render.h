/**
 * @file render.h
 * @author Ross Ning (rossning92@gmail.com)
 * @brief Utility functions for GL rendering including framebuffer creation,
 * render to texture, etc.
 * @version 0.1
 * @date 2020-08-29
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef RENDER_H
#define RENDER_H

#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>

GLuint createColorTexture(int width, int height, bool hdr = true);

struct FramebufferCreateInfo {
  GLuint colorTexture = 0;
  int width = 256;
  int height = 256;
  bool createDepthBuffer = false;
};

GLuint createFramebuffer(const FramebufferCreateInfo &info);

GLuint createQuadVAO();

struct RenderToTextureInfo {
  std::string vertexShader = "shader/simple.vert";
  std::string fragShader;
  std::map<std::string, float> floatUniforms;
  std::map<std::string, GLuint> textureUniforms;
  std::map<std::string, GLuint> cubemapUniforms;
  GLuint targetTexture;
  int width;
  int height;
};

void renderToTexture(const RenderToTextureInfo &rtti);

#endif /* RENDER_H */
