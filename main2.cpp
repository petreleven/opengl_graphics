#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

static void windowSetup();
static unsigned int width = 800;
static unsigned int height = 600;
static float triangle1[] = {
  0.5f,0.4f,0.0f,
  0.5f,-0.4f,0.0f,
  0.9f, -0.4f,0.0f,
};
static float triangle2[] = {
  0.4f,0.4f,0.0f,
  0.4f,-0.4f,0.0f,
  -0.9f, -0.4f,0.0f,
};
const std::string vertexShaderSource = 
"#version 330 core \n layout (location=0) in vec3 aPos;\n void main(){\n gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n} ";
const std::string fragmentShaderSource = 
"#version 330 core\n out vec4 FragColor;\n void main(){\n FragColor = vec4(1.0f, 0.4f, 0.2f, 1.0f);\n}";
const std::string fragmentShaderSource2 = 
"#version 330 core\n out vec4 FragColor;\n void main(){\n FragColor = vec4(0.4f, 0.4f, 0.2f, 1.0f);\n}";

int status;
char errorLog[512];

static unsigned int CreateShader(unsigned int shaderType, const std::string &sourceCode){
  
  unsigned int shader = glCreateShader(shaderType);
  const GLchar *code = reinterpret_cast<const char *>(sourceCode.c_str());
  glShaderSource(shader, 1, &code, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if(!status){
    glGetShaderInfoLog(shader, 512, NULL, errorLog);
    std::cout<<"ERROR::COMPILING::Shader "<<"\n"<<errorLog;
  }
  return shader;
}
int main(){
  windowSetup();
  GLFWwindow *window = glfwCreateWindow(width, height, "two tris", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to launch/create window" << "\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout<<"Failed to init glad"<<"/n";
  }
  //create VBO AND VAO
  unsigned int VBO[2], VAO[2];
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);

  //triangle1
  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), &triangle1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  //triangle2
  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), &triangle2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  //unbind buffers
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  //SHADER PROGRAM
  unsigned int shaderProgram, shaderProgram2,vertexShader,fragmentShader, fragmentShader2;
  shaderProgram = glCreateProgram();
  shaderProgram2 = glCreateProgram();
  vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
  fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  fragmentShader2 = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource2);

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram);
  glLinkProgram(shaderProgram2);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if (!status)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL,errorLog);
    std::cout << "ERROR::PROGRAM::LINKING FAILED\n"
              << errorLog;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteShader(fragmentShader2);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while(!glfwWindowShouldClose(window)){
    //-----------RENDER------------//
    glClearColor(0.4f, 0.3f, 0.4f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    //draw triangle1
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //draw triangle2
    glUseProgram(shaderProgram2);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    //---------SWAP BUFFERS--------//
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);
  glDeleteProgram(shaderProgram);
  glDeleteProgram(shaderProgram2);
  glfwTerminate();

  return 0;
}


static void windowSetup()
{
  //------glfw config----//
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
