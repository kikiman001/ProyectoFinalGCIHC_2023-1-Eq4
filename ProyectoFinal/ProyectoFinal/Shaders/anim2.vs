#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

const float amplitude = 0.5;
const float frequency = 0.002;
const float PI = 3.14159;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{
  //distancia entre los vertices
  float distance = length(aPos);
  //efecto del agua con trigonometria
  //desplazamiento en mis ejes
  float effect = amplitude*sin(-PI*distance*frequency+time);
  /*
  suma = desplazamiento en vertices
  multiplicacion = escalas
  */
  gl_Position = projection * view * model * vec4(aPos.x+effect, aPos.y, aPos.z, 1);
  //coordenada    U            V
   TexCoords = vec2(aTexCoords.x+effect, aTexCoords.y+effect);


}