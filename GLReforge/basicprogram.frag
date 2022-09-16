#version 450

// in  vec3 fragcolor;
in  vec2 uv_0;
in  vec3 normal_0;
in  vec3 wordpos;
in  mat3 tbn;

out vec4 color;

uniform vec3 ambient;
uniform vec3 lightcolor;
uniform vec3 lightposition;
uniform vec3 camera_world_location;

uniform float constant;
uniform float linear;
uniform float quadratic;

uniform int use_albedo_map;
uniform int use_metalic_map;
uniform int use_roughness_map;
uniform int use_ao_map;
uniform int use_normal_map;

uniform vec3 albedo;
uniform float metalic;
uniform float roughness;
uniform float ambeintocclusion;

layout (binding = 0) uniform sampler2D albedomap;
layout (binding = 1) uniform sampler2D metalicmap;
layout (binding = 2) uniform sampler2D roughnessmap;
layout (binding = 3) uniform sampler2D ambeintocclusionmap;
layout (binding = 4) uniform sampler2D normalmap;


const float oneoverpi = 0.318309886f;
const float pi		  = 3.141592653f;

vec3 lambert_diffuse(vec3 color_value, vec3 fernel, float metalic){

	return (1.0f - fernel) * (1.0f - metalic) * color_value * oneoverpi;
}

float specular_d(vec3 h, vec3 n, float roughness){


	float alpha = roughness * roughness;
	float alpha_square = alpha * alpha;
	float ndoth = max(dot(n, h), 0.0f);
	ndoth *= ndoth;

	float dominator = (ndoth * (alpha_square - 1.0f) + 1.0f) * (ndoth * (alpha_square - 1.0f) + 1.0f);
	return alpha_square * oneoverpi / (dominator + 0.0001f);
}

float specular_g(vec3 l, vec3 v, vec3 n, float roughness){
	
	float resampled_roughness = 0.5f * (roughness +  1.0f);
	float alpha = resampled_roughness * resampled_roughness;

	// float k = 0.125f * ( alpha + 1.0f ) * ( alpha + 1.0f ); // ue does not use this any more
    float k = alpha * 0.5f;
	float ndotv = max(dot(n,v), 0.0f);
	float ndotl = max(dot(n,l), 0.0f);

	float g1 = ndotv / ((ndotv * ( 1.0f - k)) + k);
	float g2 = ndotl / ((ndotl * ( 1.0f - k)) + k);

	return g1 * g2;
}

vec3 specular_f(vec3 f0, vec3 v, vec3 h){

	float vdoth = max(dot(v, h), 0.0f);
	float power = (-5.55473f * vdoth - 6.98316f) * vdoth; 
	return f0 + (1.0f - f0) * exp2(power);
}


vec3 brdf(vec3 l, vec3 v, vec3 n, vec3 f, float d, float g){
	vec3 final_brdf;
	float ndotl = max(dot(n, l), 0.0f);
	float ndotv = max(dot(n, v), 0.0f);
	final_brdf = (d * f * g) / ((4.0f * ndotl * ndotv) + 0.00001f);
	return final_brdf;
}

vec3 compute_bumps_via_normalmap(){
	
	vec3 bumps = texture(normalmap, uv_0).xyz;
	bumps = normalize(2.0f * bumps - 1.0f);

	vec3 detailed_normal = tbn * bumps;
	return normalize(detailed_normal);

}

void main (){
	// set up our directions and vectors
	vec3 normalized_normal = normalize(normal_0);
	if (use_normal_map == 1) {
		normalized_normal = compute_bumps_via_normalmap();
	}

	vec3 light_direction = normalize(lightposition - wordpos);

	vec3 view_direction = normalize(camera_world_location - wordpos);

	// vec3 reflection_direction = reflect(view_direction, normalized_normal);

	vec3 half_vector_direction = normalize(view_direction + light_direction);
	
	float vertex_light_distance = length(wordpos - lightposition); 

	float attenuation = constant + linear * vertex_light_distance + quadratic * vertex_light_distance * vertex_light_distance;

	attenuation = 1.0f / attenuation;

	vec3 albedo_value;
    float metalic_value;
    float specular_value;
    float roughness_value;
    float ambeintocclusion_value;
	float alpha;
	/* set up values */
	if(use_albedo_map == 1){
		albedo_value = texture(albedomap, uv_0).rgb;
		alpha = texture(albedomap, uv_0).a;
	}
	else{
		albedo_value = albedo;
		alpha = 1.0f;
	}

	if(use_metalic_map == 1){
		metalic_value = texture(metalicmap, uv_0).b;
	}
	else{
		metalic_value = metalic;
	}

    if(use_roughness_map == 1){
		roughness_value = texture(roughnessmap, uv_0).g;
	}
	else{
		roughness_value = roughness;
	}
	
	if(use_ao_map == 1){
		ambeintocclusion_value = texture(ambeintocclusionmap, uv_0).r;
	}
	else{
		ambeintocclusion_value = ambeintocclusion;

	}

	vec3 f0 = vec3(0.04f);
	f0 = mix(f0, albedo_value, metalic_value);

	float ndotl = max(dot(normalized_normal, light_direction), 0.0);
	/* this should be changed */
	vec3 ambient_final = ambient  * albedo_value * ambeintocclusion_value;

	/* compute the actual lighting here */
	vec3 Lo = vec3(0.0f);
	vec3 light_radience =  lightcolor * 10.0f * attenuation;
	float d = specular_d(half_vector_direction, normalized_normal, roughness_value); 
	float g = specular_g(light_direction, view_direction, normalized_normal, roughness_value);
	vec3  f = specular_f(f0, view_direction, half_vector_direction);
	vec3  brdf_specular = brdf(light_direction, view_direction, normalized_normal, f, d, g);
	vec3  diffuse_brdf =  lambert_diffuse(albedo_value, f, metalic_value);


	Lo = ambient_final + (diffuse_brdf + brdf_specular) * light_radience * ndotl; 
	color = vec4(Lo, alpha);
}