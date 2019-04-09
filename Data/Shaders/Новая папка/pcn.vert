#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 inNormal;

layout (binding = 0) uniform UBO 
{
	mat4 model;
	mat4 view;
	mat4 projection;
	mat4 mvp;
	
} ubo;

layout (location = 0) out vec3 outColor;
layout (location = 1) out vec3 outWorldPosition;
layout (location = 2) out vec3 outNormal;

out gl_PerVertex {
	vec4 gl_Position;
};

void main() 
{
	//mat4 _model;
	//_model[0].xyzw = vec4(1.0f, 0.0f, 0.0f, 0.0f);
	//_model[1].xyzw = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	//_model[2].xyzw = vec4(0.0f, 0.0f, 1.0f, 0.0f);
	//_model[3].xyzw = vec4(5.0f, 0.0f, 0.0f, 1.0f);
	vec3 locPos = vec3(ubo.model * vec4(inPos, 1.0));
	outWorldPosition = locPos;

	outNormal = mat3(ubo.model) * inNormal;


	outColor = inColor;
	mat4 _mvp = ubo.projection * ubo.view * ubo.model;
	gl_Position = _mvp * vec4(inPos.xyz, 1.0);
	//mat4 temp_mvp;
	//gl_Position = temp_mvp * vec4(inPos.xyz, 1.0);
	//gl_Position = vec4(inPos.x / 3, inPos.y / 3, inPos.z, 1.0);
}
