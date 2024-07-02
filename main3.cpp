#include "./glad/glad.h"
#include "Core/Shader.h"
#include "Core/TextureLoader.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

void windowSetup();
void framebuffer_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, float &blend);
float vertices[] = {
    // positions          // colors           // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
};
unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3};
int main()
{
  windowSetup();
  //---------window------;
  GLFWwindow *window = glfwCreateWindow(800, 600, "learn", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to launch/create window" << "\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_callback);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to init GLAD" << "\n";
  }

  //---------our code----//
  Shader ourShader("../shaders/vertex.vs", "../shaders/fragment.fs");
  unsigned int VA0, VB0, EB0;
  glGenVertexArrays(1, &VA0);
  glGenBuffers(1, &VB0);
  glGenBuffers(1, &EB0);
  glBindVertexArray(VA0);
  // select buffer object and give data
  glBindBuffer(GL_ARRAY_BUFFER, VB0);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // select element buffer object and sequence of drawing
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EB0);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture 1
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  float offset = 0.0f;
  // load and create texture
  //---------------------
  // texture 1
  //-----------
  TextureLoader container = TextureLoader("/home/peter/Downloads/learn/container.jpg", 0);
  uint texture = container.GetTextureId();
  TextureLoader container2 = TextureLoader("/home/peter/Downloads/learn/a.jpg", 0);
  uint texture2 = container2.GetTextureId();

  ourShader.use();
  ourShader.setInt("texture1", 0);
  ourShader.setInt("texture2", 1);
  float blend = 0.0f;
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window))
  {
    // PROCESS INPUT
    processInput(window, blend);
    //---CLEAR--
    glClearColor(0.2f, 0.5f, 0.4f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //--bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //----RENDER-----//
    ourShader.use();
    ourShader.setFloat("blend", blend);
    glBindVertexArray(VA0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //---SWAP BUFFERS---//
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VA0);
  glDeleteBuffers(1, &VB0);
  glDeleteBuffers(1, &EB0);
  glfwTerminate();
}

void windowSetup()
{
  //------glfw config----//
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, float &blend)
{
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
  {
    blend += 0.1;
    blend = std::max(0.0f, std::min(blend, 1.0f));
  }
  else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
  {
    blend -= 0.1;
    blend = std::max(0.0f, std::min(blend, 1.0f));
  }
}
