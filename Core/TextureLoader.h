#pragma once

#include "../glad/glad.h"
#include <string>
#include <GLFW/glfw3.h>
#include <iostream>

class TextureLoader
{
private:
  unsigned char *data;
  int width;
  int height;
  int nChannels;
  uint textureId;
  void loadImage();

public:
  TextureLoader(std::string texturePath, uint imageFormat);
  uint GetTextureId() const;
};
