#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader/stb_image.h"

TextureLoader::TextureLoader(std::string texturePath, uint imageFormat)
{
  glGenTextures(1, &this->textureId);
  glBindTexture(GL_TEXTURE_2D, this->textureId);
  // WRAP MODE AND FILTER
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image data
  this->data = stbi_load(texturePath.c_str(), &this->width, &this->height, &this->nChannels, 0);
  stbi_set_flip_vertically_on_load(true);
  if (data)
  {
    switch (imageFormat)
    {
    case 0:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      break;
    case 1:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      break;
    default:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
      break;
    }
  }
  else{
    std::cout<<"ERROR::Texture::Failed to load texture \n"<<stbi_failure_reason();
  }
  stbi_image_free(data);
}

uint TextureLoader::GetTextureId() const{
  return this->textureId;
}
