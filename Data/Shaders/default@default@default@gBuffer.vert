#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// входные параметры
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 inNormal;

// выходные параметры
layout (location = 0) out vec3 outPosition;
layout (location = 1) out vec3 outColor;
layout (location = 2) out vec3 outNormal;

layout (binding = 0) uniform UBO 
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 mvp;
	
} ubo;

void main() {

	outPosition 	= vec3(mat3(ubo.model) * inPosition);
	outColor 		= inColor;
	outNormal 		= mat3(ubo.model) * inNormal;
	
	mat4 _mvp = ubo.projection * ubo.view * ubo.model;
	gl_Position = _mvp * vec4(inPosition.xyz, 1.0f);
	
}