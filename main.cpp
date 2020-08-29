/**
 * @file main.cpp
 * @author Ross Ning (rossning92@gmail.com)
 * @brief Real-time black hole rendering in OpenGL.
 * @version 0.1
 * @date 2020-08-29
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <assert.h>
#include <map>
#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <imgui.h>

#include "GLDebugMessageCallback.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "render.h"
#include "shader.h"
#include "texture.h"

static const int SCR_WIDTH = 1920;
static const int SCR_HEIGHT = 1080;

static float mouseX, mouseY;

#define IMGUI_TOGGLE(NAME, DEFAULT)                                            \
  static bool NAME = DEFAULT;                                                  \
  ImGui::Checkbox(#NAME, &NAME);                                               \
  rtti.floatUniforms[#NAME] = NAME ? 1.0f : 0.0f;

#define IMGUI_SLIDER(NAME, DEFAULT, MIN, MAX)                                  \
  static float NAME = DEFAULT;                                                 \
  ImGui::SliderFloat(#NAME, &NAME, MIN, MAX);                                  \
  rtti.floatUniforms[#NAME] = NAME;

static void glfwErrorCallback(int error, const char *description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void mouseCallback(GLFWwindow *window, double x, double y) {
  static float lastX = 400.0f;
  static float lastY = 300.0f;
  static float yaw = 0.0f;
  static float pitch = 0.0f;
  static float firstMouse = true;

  mouseX = (float)x;
  mouseY = (float)y;
}

class PostProcessPass {
private:
  GLuint program;

public:
  PostProcessPass(const std::string &fragShader) {
    this->program = createShaderProgram("shader/simple.vert", fragShader);

    glUseProgram(this->program);
    glUniform1i(glGetUniformLocation(program, "texture0"), 0);
    glUseProgram(0);
  }

  void render(GLuint inputColorTexture, GLuint destFramebuffer = 0) {
    glBindFramebuffer(GL_FRAMEBUFFER, destFramebuffer);

    glDisable(GL_DEPTH_TEST);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(this->program);

    glUniform2f(glGetUniformLocation(this->program, "resolution"),
                (float)SCR_WIDTH, (float)SCR_HEIGHT);

    glUniform1f(glGetUniformLocation(this->program, "time"),
                (float)glfwGetTime());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, inputColorTexture);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(0);
  }
};

int main(int, char **) {
  // Setup window
  glfwSetErrorCallback(glfwErrorCallback);
  if (!glfwInit())
    return 1;

  // Create window with graphics context
  glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Wormhole", NULL, NULL);
  if (window == NULL)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetWindowPos(window, 0, 0);

  bool err = glewInit() != GLEW_OK;
  if (err) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    return 1;
  }

  {
    // Enable the debugging layer of OpenGL
    //
    // GL_DEBUG_OUTPUT - Faster version but not useful for breakpoints
    // GL_DEBUG_OUTPUT_SYNCHRONUS - Callback is in sync with errors, so a
    // breakpoint can be placed on the callback in order to get a stacktrace for
    // the GL error. (enable together with GL_DEBUG_OUTPUT !)

    glEnable(GL_DEBUG_OUTPUT);
    // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    // Set the function that will be triggered by the callback, the second
    // parameter is the data parameter of the callback, it can be useful for
    // different contexts but isn't necessary for our simple use case.
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);
  }

  {

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
    // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  }

  GLuint fboBlackhole, texBlackhole;
  texBlackhole = createColorTexture(SCR_WIDTH, SCR_HEIGHT);

  FramebufferCreateInfo info = {};
  info.colorTexture = texBlackhole;
  if (!(fboBlackhole = createFramebuffer(info))) {
    assert(false);
  }

  GLuint quadVAO = createQuadVAO();
  glBindVertexArray(quadVAO);

  // Main loop
  PostProcessPass passthrough("shader/passthrough.frag");

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::ShowDemoWindow();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // renderScene(fboBlackhole);

    static GLuint galaxy = loadCubemap("assets/skybox_nebula_dark");
    static GLuint colorMap = loadTexture2D("assets/color_map.png");
    static GLuint uvChecker = loadTexture2D("assets/uv_checker.png");

    static GLuint texBlackhole = createColorTexture(SCR_WIDTH, SCR_HEIGHT);
    {
      RenderToTextureInfo rtti;
      rtti.fragShader = "shader/blackhole_main.frag";
      rtti.cubemapUniforms["galaxy"] = galaxy;
      rtti.textureUniforms["colorMap"] = colorMap;
      rtti.floatUniforms["mouseX"] = mouseX;
      rtti.floatUniforms["mouseY"] = mouseY;
      rtti.targetTexture = texBlackhole;
      rtti.width = SCR_WIDTH;
      rtti.height = SCR_HEIGHT;

      IMGUI_TOGGLE(gravatationalLensing, true);
      IMGUI_TOGGLE(renderBlackHole, true);
      IMGUI_TOGGLE(mouseControl, true);
      IMGUI_SLIDER(cameraRoll, 0.0f, -180.0f, 180.0f);
      IMGUI_TOGGLE(frontView, false);
      IMGUI_TOGGLE(topView, false);
      IMGUI_TOGGLE(adiskEnabled, true);
      IMGUI_TOGGLE(adiskParticle, true);
      IMGUI_SLIDER(adiskDensityV, 2.0f, 0.0f, 10.0f);
      IMGUI_SLIDER(adiskDensityH, 4.0f, 0.0f, 10.0f);
      IMGUI_SLIDER(adiskHeight, 0.55f, 0.0f, 1.0f);
      IMGUI_SLIDER(adiskLit, 0.25f, 0.0f, 4.0f);
      IMGUI_SLIDER(adiskNoiseLOD, 5.0f, 1.0f, 12.0f);
      IMGUI_SLIDER(adiskNoiseScale, 0.8f, 0.0f, 10.0f);
      IMGUI_SLIDER(adiskSpeed, 0.5f, 0.0f, 1.0f);

      renderToTexture(rtti);
    }

    static GLuint texBrightness = createColorTexture(SCR_WIDTH, SCR_HEIGHT);
    {
      RenderToTextureInfo rtti;
      rtti.fragShader = "shader/bloom_brightness_pass.frag";
      rtti.textureUniforms["texture0"] = texBlackhole;
      rtti.targetTexture = texBrightness;
      rtti.width = SCR_WIDTH;
      rtti.height = SCR_HEIGHT;
      renderToTexture(rtti);
    }

    const int MAX_BLOOM_ITER = 8;
    static GLuint texDownsampled[MAX_BLOOM_ITER];
    static GLuint texUpsampled[MAX_BLOOM_ITER];
    if (texDownsampled[0] == 0) {
      for (int i = 0; i < MAX_BLOOM_ITER; i++) {
        texDownsampled[i] =
            createColorTexture(SCR_WIDTH >> (i + 1), SCR_HEIGHT >> (i + 1));
        texUpsampled[i] = createColorTexture(SCR_WIDTH >> i, SCR_HEIGHT >> i);
      }
    }

    static int bloomIterations = MAX_BLOOM_ITER;
    ImGui::SliderInt("bloomIterations", &bloomIterations, 1, 8);
    for (int level = 0; level < bloomIterations; level++) {
      RenderToTextureInfo rtti;
      rtti.fragShader = "shader/bloom_downsample.frag";
      rtti.textureUniforms["texture0"] =
          level == 0 ? texBrightness : texDownsampled[level - 1];
      rtti.targetTexture = texDownsampled[level];
      rtti.width = SCR_WIDTH >> (level + 1);
      rtti.height = SCR_HEIGHT >> (level + 1);
      renderToTexture(rtti);
    }

    for (int level = bloomIterations - 1; level >= 0; level--) {
      RenderToTextureInfo rtti;
      rtti.fragShader = "shader/bloom_upsample.frag";
      rtti.textureUniforms["texture0"] = level == bloomIterations - 1
                                             ? texDownsampled[level]
                                             : texUpsampled[level + 1];
      rtti.textureUniforms["texture1"] =
          level == 0 ? texBrightness : texDownsampled[level - 1];
      rtti.targetTexture = texUpsampled[level];
      rtti.width = SCR_WIDTH >> level;
      rtti.height = SCR_HEIGHT >> level;
      renderToTexture(rtti);
    }

    static GLuint texBloomFinal = createColorTexture(SCR_WIDTH, SCR_HEIGHT);
    {
      RenderToTextureInfo rtti;
      rtti.fragShader = "shader/bloom_composite.frag";
      rtti.textureUniforms["texture0"] = texBlackhole;
      rtti.textureUniforms["texture1"] = texUpsampled[0];
      rtti.targetTexture = texBloomFinal;
      rtti.width = SCR_WIDTH;
      rtti.height = SCR_HEIGHT;

      IMGUI_SLIDER(bloomStrength, 0.1f, 0.0f, 1.0f);

      renderToTexture(rtti);
    }

    static GLuint texTonemapped = createColorTexture(SCR_WIDTH, SCR_HEIGHT);
    {
      RenderToTextureInfo rtti;
      rtti.fragShader = "shader/tonemapping.frag";
      rtti.textureUniforms["texture0"] = texBloomFinal;
      rtti.targetTexture = texTonemapped;
      rtti.width = SCR_WIDTH;
      rtti.height = SCR_HEIGHT;

      IMGUI_TOGGLE(tonemappingEnabled, true);
      IMGUI_SLIDER(gamma, 2.5f, 1.0f, 4.0f);

      renderToTexture(rtti);
    }

    passthrough.render(texTonemapped);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // // Cleanup
  // ImGui_ImplOpenGL3_Shutdown();
  // ImGui_ImplGlfw_Shutdown();
  // ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
