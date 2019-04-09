#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// входные параметры
layout (location = 0) in vec3 outWorldPos;
layout (location = 1) in vec3 outColor;
layout (location = 2) in vec3 outNormal;
layout (location = 4) in vec3 outLight;

layout (location = 0) out vec4 outFragColor;

const vec4 diffColor = vec4 ( 0.5, 0.0, 0.0, 1.0f );

void main() 
{

	vec3 lightNorm   = normalize ( outLight );
	vec3 normalNorm   = normalize ( outNormal );
	
	vec4 diff = diffColor * max ( dot ( normalNorm, lightNorm ), 0.0 );
	
	outFragColor = diff;
	
	//outFragColor = vec4(outColor, 1.0f);
}