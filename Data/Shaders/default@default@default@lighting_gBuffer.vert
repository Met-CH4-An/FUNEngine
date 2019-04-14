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
	
	gl_Position = vec4(inPosition.xyz, 1.0f);
	
	//vec2 outUV = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
	//gl_Position = vec4(outUV * 1.0f - 1.0f, 0.0f, 1.0f);
	
	//vec2 pos[3] = vec2[3]( 	vec2(0.7, 0.7),
	//						vec2(-0.7, 0.7),                           
	//						vec2(0.0, -0.7) );
    //gl_Position = vec4( pos[gl_VertexIndex], 0.0, 1.0 );
	
}