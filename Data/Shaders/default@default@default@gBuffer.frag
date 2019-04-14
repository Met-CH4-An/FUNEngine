#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// входные параметры
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 inNormal;

// выходные параметры
layout (location = 0) out vec4 outFragColor;
layout (location = 1) out vec4 outPosition;
layout (location = 2) out vec4 outColor;
layout (location = 3) out vec4 outNormal;

void main() {

	outFragColor 	= vec4(0.0f, 1.0f, 1.0f, 1.0f);
	outPosition 	= vec4(inPosition, 1.0f);	
	outColor 		= vec4(inColor, 1.0f);	
	outNormal 		= vec4(inNormal, 1.0f);
	
}