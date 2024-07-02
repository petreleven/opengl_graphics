#include "Shader.h"


Shader::Shader(const char *vertexPath, const char *fragmentPath){
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  //allow ifstream to throw exceptions
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try{
    vShaderFile.open(vertexPath);
    if (!vShaderFile.is_open()){
      throw std::ifstream::failure("FAILED TO OPEN VERTEX FILE");
    }
    fShaderFile.open(fragmentPath);
    if (!fShaderFile.is_open()){
      throw std::ifstream::failure("FAILED TO OPEN FRAGMENT FILE");
    }
    std::stringstream vShaderStream, fShaderStream;
    //read contents into streams
    vShaderStream<<vShaderFile.rdbuf();
    fShaderStream<<fShaderFile.rdbuf();
    //close file handlers
    vShaderFile.close();
    fShaderFile.close();
    //convert stream to string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e){
    std::cout<<"ERROR::SHADER::READING SHADER FILE"<<"\n";
  }

  const char * vShaderCode = vertexCode.c_str();
  const char * fShaderCode =fragmentCode.c_str();

  //Compile shader and link them to Program
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];
  vertex = glCreateShader(GL_VERTEX_SHADER);
  fragment= glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success){
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout<<"ERROR::SHADER::VERTEX::COMPILATION\n"<<infoLog;
  }
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success){
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION\n"<<infoLog;
  }
  //shader program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertex);
  glAttachShader(this->ID, fragment);
  glLinkProgram(this->ID);
  glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
  if (!success){
    glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
    std::cout<<"ERROR::SHADER::PROGRAM::LINKING\n"<<infoLog;
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use(){
  glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const{
  unsigned int location =glGetUniformLocation(this->ID, name.c_str());
  glUniform1i(location, int(value));

}

void Shader::setInt(const std::string &name, int value) const{
  unsigned int location =glGetUniformLocation(this->ID, name.c_str());
  glUniform1i(location, value);

}

void Shader::setFloat(const std::string &name, float value) const{
  unsigned int location =glGetUniformLocation(this->ID, name.c_str());
  glUniform1f(location, value);
}
