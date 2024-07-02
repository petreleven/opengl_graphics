#include "glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

void framebuffer_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void windowSetup();

/* float vertices[] = {-0.5f, -0.5f, 0.f,
                    0.5f, -0.5f, 0.f,
                    0.0f, 0.5f, 0.f}; */
float vertices[] = {
    0.0f, 0.5f, 0.0f, 1.0f, 0.f , 0.f,  // top right
    0.5f, -0.5f, 0.0f, 0.f, 1.0f, 0.f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.f, 0.0f, 1.0f,// bottom left
};
unsigned int indices[] = {
    0, 1, 3,  // first triangle
    1, 2, 3}; // second triangle
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location=0) in vec3 aPos; \n"
                                 "layout (location=1) in vec3 aColor; \n"
                                 "out vec3 ourColor;"
                                 "void main(){ \n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "ourColor = aColor;\n"
                                 "} \0";
const char *fragmetShaderSource = "#version 330 core\n"
                                  "out vec4 FragColor;\n"
                                  "in vec3 ourColor; \n"
                                  "void main(){\n"
                                  "  FragColor = vec4(ourColor, 1.0);\n"
                                  "}\0";

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
  ///--------load openGL func pntrs---//

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to init GLAD" << "\n";
  }

  //------------------//
  //---SHADER SETUP-----//
  //-------------------//
  unsigned int vertexShader;
  unsigned int fragmetShader;
  int success;
  char infoLog[512];
  {
    //--COMPLILING SHADER SOURCE ------//
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILIATION FAIL\n"
                << infoLog;
    }
    //--------FRAGMENT SHADER---//
    fragmetShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmetShader, 1, &fragmetShaderSource, NULL);
    glCompileShader(fragmetShader);
    glGetShaderiv(fragmetShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(fragmetShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILIATION FAIL\n"
                << infoLog;
    }
  }
  //-------LINKING SHADERS---------/
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmetShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::PROGRAM::LINKING FAILED\n"
              << infoLog;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmetShader);

  //-------------------------------//
  //----USING vertex array object & VB0--//
  //-------------------------------//
  unsigned int VA0, VBO;
  glGenVertexArrays(1, &VA0);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VA0);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // ALLOW UNBINDING
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  //----------gameloop------------//
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window))
  {
    //--GET INPUT--//
    processInput(window);
    //--RENDER--//
    glClearColor(0.2f, 0.5f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VA0);
    glDrawArrays(GL_TRIANGLES,0, 3);
    glBindVertexArray(0);
    //--SWAP BUFFERS
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VA0);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}

void framebuffer_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

void windowSetup()
{
  //------glfw config----//
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
