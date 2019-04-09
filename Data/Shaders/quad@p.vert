#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// входные параметры
layout (location = 0) in vec3 inPosition;

layout (binding = 0) uniform UBO 
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 mvp;
	
} ubo;

void main() {	
	
	mat4 _mvp;
	gl_Position = vec4(inPosition.xyz, 1.0f);
	
}