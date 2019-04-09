#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// входные параметры - атрибуты
layout (location = 0) in vec3 a_Position;

// входные параметры - UBO
layout (binding = 0) uniform Positioning {
	mat4 m_Model;
	mat4 m_View;
	mat4 m_Projection;
	mat4 m_MVP;
} u_Positioning;

// выходные параметры
layout (location = 0) out vec3 outWorldPos;

void main() 
{
	// координаты в мировом пространстве
	outWorldPos = vec3(mat3(u_Positioning.m_Model) * a_Position);

	//
	gl_Position = u_Positioning.m_MVP * vec4(a_Position.xyz, 1.0);
	
}