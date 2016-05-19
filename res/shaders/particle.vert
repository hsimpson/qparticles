//[vertex shader]
#version 410 core



// inputs
in vec3 vertex;
in vec4 color;

// uniforms
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;

// outputs
out VertexData
{
    vec4 color;
} vertexData;

smooth out vec4 vertexColor;

void main(void)
{
  // set the position
  gl_Position = vec4(vertex, 1.0);
  vertexData.color = color;
  vertexColor = color;
}