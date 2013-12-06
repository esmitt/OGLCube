#version 400

uniform mat4 mView, mProjection, mModel;

layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec4 vColor;

out vec4 vColorVs;

void main()
{
	vColorVs = vColor;
	gl_Position = mProjection * mView * mModel * vVertex;
}