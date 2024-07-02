#version 330 core
out vec4 fragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blend;

void main(){
  //fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  //fragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 10);
  fragColor = mix(texture(texture1, TexCoord) , texture(texture2, TexCoord), blend);
}
