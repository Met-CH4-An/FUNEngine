#version 450

#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

const float PI = 3.14159265359f;

vec3 camPosition = vec3(0.0f, 0.0f, 20.0f);
vec3 lthPosition = vec3(-10.0f, 0.0f, 0.0f);
vec4 lights[4];

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec3 inWorldPosition;
layout (location = 2) in vec3 inNormal;

struct Material_PBR {

	float m_Roughness;
	vec3 m_FR;
	vec3 m_Albedo;
};


layout (location = 0) out vec4 outFragColor;
//layout (location = 1) out vec4 outFragColor1;

float G_SchlicksmithGGX(float dotNL, float dotNV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;
	float GL = dotNL / (dotNL * (1.0 - k) + k);
	float GV = dotNV / (dotNV * (1.0 - k) + k);
	return GL * GV;
}

float GGX_PartialGeometry(float cosThetaN, float alpha) {
	
		float cosTheta_sqr = clamp(cosThetaN*cosThetaN, 0.0, 1.0);
     	float tan2 = ( 1 - cosTheta_sqr ) / cosTheta_sqr;
    	float GP = 2 / ( 1 + sqrt( 1 + alpha * alpha * tan2 ) );
		
    	return GP;
}

float GGX_Distribution(float cosThetaNH, float alpha) {
    float alpha2 = alpha * alpha;
	float NH_sqr = clamp(cosThetaNH*cosThetaNH, 0.0, 1.0);
    float den = NH_sqr * alpha2 + (1.0 - NH_sqr);
    return alpha2 / ( PI * den * den );
}

vec3 FresnelSchlick(vec3 FR, float cosTheta) {
    return FR + (1.0 - FR) * pow(1.0 - clamp(cosTheta, 0.0, 1.0), 5.0);
	//return 0.0f;
}

void main() 
{

	lights[0] = vec4(-50.0f, 0.0f, 0.0f, 1.0f);
	lights[1] = vec4(50.0f, 0.0f, 0.0f, 1.0f);
	lights[2] = vec4(0.0f, 50.0f, 0.0f, 1.0f);
	lights[3] = vec4(0.0f, -50.0f, 0.0f, 1.0f);

	Material_PBR _materialPBR;
	_materialPBR.m_Roughness = 0.35f;
	_materialPBR.m_FR = vec3(0.24, 0.24, 0.24);
	//_materialPBR.m_Albedo = vec3(0.86, 0.176, 0);
	_materialPBR.m_Albedo = vec3(0.50, 0.50, 0.50);

	vec3 N = normalize(inNormal);
	vec3 V = normalize(camPosition - inWorldPosition);
	float dotNV = clamp(dot(N,V), 0.0, 1.0);
	
	vec4 _color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	for(int i = 0; i < 4; ++i) {
	
		vec3 L = normalize(lights[i].xyz - inWorldPosition);
		vec3 H = normalize (V + L);
		
		float dotNL = clamp(dot(N,L), 0.0, 1.0);
		float dotNH = clamp(dot(N,H), 0.0, 1.0);
		float dotHV = clamp(dot(H,V), 0.0, 1.0);
		
		//dotNV = dot(N,V);
		//dotNL = dot(N,L);
		
		float G;
		float D;
		vec3 F;
		//if (dotNL > 0.0) {
	
		float roug_sqr = _materialPBR.m_Roughness * _materialPBR.m_Roughness;
		float GV = GGX_PartialGeometry(dotNV, roug_sqr);
		float GL = GGX_PartialGeometry(dotNL, roug_sqr);
		G = GV * GL;
		
		D = GGX_Distribution(dotNH, roug_sqr);
		
		F = FresnelSchlick(_materialPBR.m_FR, dotHV);
		
		vec3 specK = G*D*F*0.25 / dotNV;
		vec3 diffK = clamp(1.0-F, 0.0, 1.0);
		vec3 asd = max(vec3(0.0f, 0.0f, 0.0f), _materialPBR.m_Albedo * diffK * dotNL / PI + specK);
		_color += vec4(asd, 1.0);
	
		//G = G_SchlicksmithGGX(dotNL, dotNV, 0.1);
		//G = dotNL;
		
		//_color = vec4(dotHV, dotHV, dotHV, 1.0);
		//_color = vec4(F, 1.0);
	
		//}
	}
	outFragColor = _color;
	//outFragColor1 = _color;
	//if(outFragColor.r > 1.000001) {
	//outFragColor.r = 0.0;
	//outFragColor.g = 0.0;
	//outFragColor.b = 0.0;
	//}
	//outFragColor = vec4(1.0, 0.5, 0.1, 1.0);

  	
}