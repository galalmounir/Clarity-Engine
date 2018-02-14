#version 410 core
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

out vec3 myColor;

// Values that stay constant for the whole mesh.
uniform highp mat4 MVP;

void main()
{
    myColor = vertex_colour;
	gl_Position = MVP * vec4(vertex_position,1.0f);

}
