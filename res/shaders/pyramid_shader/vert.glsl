#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;


out vec3 pass_colour;

uniform mat4 uni_M;
uniform mat4 uni_VP;
uniform sampler2D heightmap;  // heightmap texture
void main()
{
	vec3 pos=vec3(position*0.1);
	vec4 world_position = uni_M * vec4(pos, 1.0);
	gl_Position = uni_VP * world_position;
	
	pass_colour = colour;
}