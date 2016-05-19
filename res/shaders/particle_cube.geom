//[geometry SHADER]
#version 410

layout (points) in;
layout (points) out;
//layout (triangle_strip) out;
layout (max_vertices = 1) out;



in VertexData
{
    vec4 color;
} vertexData[];

// uniforms
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;

smooth out vec4 vertexColor;
 
void main()
{
  float half = 0.2f;
  //for (int i = 0; i < gl_in.length(); i++) 
  mat4 MVP = projectionMatrix * viewMatrix * modelViewMatrix;
  //mat4 MVP = viewMatrix * projectionMatrix;
  vertexColor = vertexData[0].color;

  
  gl_Position = MVP * (gl_in[0].gl_Position);    
  EmitVertex();
  EndPrimitive();
  
  
  
  /*
  // front
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half, -half, -half, 1.0));
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half,  half, -half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4( half, -half, -half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4( half,  half, -half, 1.0));    
  EmitVertex();
  EndPrimitive();
  */
  

  /*
  //left
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half, -half, half, 1.0));
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half,  half, half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half, -half,-half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half,  half,-half, 1.0));    
  EmitVertex();
  EndPrimitive();
  */

  /*
  //right
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(half, -half, half, 1.0));
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(half,  half, half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(half, -half,-half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(half,  half,-half, 1.0));    
  EmitVertex();
  EndPrimitive();
  */
  /*
  // back
  gl_Position = MVP * (gl_in[0].gl_Position + vec4( half, -half, half, 1.0));
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4( half,  half, half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half, -half, half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half,  half, half, 1.0));    
  EmitVertex();
  EndPrimitive();
  */

  /*
  // top
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half,  half,  half, 1.0));
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half,  half, -half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4( half,  half,  half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4( half,  half, -half, 1.0));    
  EmitVertex();
  EndPrimitive();
  */

  /*
  // bottom
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half, -half, -half, 1.0));
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4(-half, -half,  half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4( half, -half, -half, 1.0));    
  EmitVertex();
  gl_Position = MVP * (gl_in[0].gl_Position + vec4( half, -half,  half, 1.0));    
  EmitVertex();
  EndPrimitive();
  */
}