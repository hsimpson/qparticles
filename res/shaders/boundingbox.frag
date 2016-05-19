//[vertex shader]
#version 410 core



// inputs
smooth in vec4 vertexColor;

// outputs
out vec4 fragColor;

void main(void)
{
  fragColor = vertexColor;
  //fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
