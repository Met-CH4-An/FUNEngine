#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (input_attachment_index = 0, binding = 0) uniform subpassInput samplerPosition;
layout (input_attachment_index = 1, binding = 1) uniform subpassInput samplerColor;
layout (input_attachment_index = 2, binding = 2) uniform subpassInput samplerNormal;

layout (location = 0) out vec4 outFragColor;

void main() 
{
	// get g-buffer value
	vec3 _position = subpassLoad(samplerPosition).rgb;
	vec3 _color = subpassLoad(samplerColor).rgb;
	vec3 _normal = subpassLoad(samplerNormal).rgb;
	
	outFragColor = vec4(_position, 1.0f);
}