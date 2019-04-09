#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// атрибуты вершины
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 inNormal;

layout (binding = 0) uniform UBO 
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 mvp;
	
} ubo;

out gl_PerVertex 
{
    vec4 gl_Position;   
};

void main() 
{	

	// координаты в мировом пространстве
	outWorldPos = vec3(mat3(ubo.model) * inPosition);
	
	//outColor = materialVariables.m_Albedo;
	
	// нормали в мировом пространстве
	outNormal = mat3(ubo.model) * inNormal;
	
	mat4 _mvp = ubo.projection * ubo.view * ubo.model;
	gl_Position = _mvp * vec4(inPos.xyz, 1.0);
	
}