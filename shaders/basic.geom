#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec4 vColorVs[];

out vec4 vVertexColor;

void main()
{	
  for(int k = 0; k < gl_in.length(); k++)
  {
    gl_Position = gl_in[k].gl_Position;
		vVertexColor = vColorVs[k];
    EmitVertex();
  }
  EndPrimitive();
}
