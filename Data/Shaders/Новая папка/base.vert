#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// атрибуты вершины
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 inNormal;

// выходные параметры
layout (location = 0) out vec3 outWorldPos;
layout (location = 1) out vec3 outColor;
layout (location = 2) out vec3 outNormal;
layout (location = 4) out vec3 outLight;

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

	 outColor = inColor;
	// координаты в мировом пространстве
	outWorldPos = vec3(mat3(ubo.model) * inPosition);
	//outWorldPos = inPosition;
	//outWorldPos = vec3(inPosition.x, 0.0f, 0.0f);

	const vec4 lightPosition = vec4(0.0f, 0.0f, 10.0f, 1.0f );
	outLight = normalize ( vec3 ( lightPosition ) - outWorldPos ); 
	
	// нормали в мировом пространстве
	outNormal = mat3(ubo.model) * inNormal;
	
	mat4 _mvp = ubo.projection * ubo.view * ubo.model;
	gl_Position = _mvp * vec4(inPosition.xyz, 1.0);
	
}