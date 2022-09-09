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
uniform int use_specular_map;
uniform int use_roughness_map;
uniform int use_ao_map;
uniform int use_normal_map;

uniform vec3 albedo;
uniform float metalic;
uniform float specular;
uniform float roughness;
uniform float ambeintocclusion;

layout (binding = 0) uniform sampler2D albedomap;
layout (binding = 1) uniform sampler2D metalicmap;
layout (binding = 2) uniform sampler2D specularmap;
layout (binding = 3) uniform sampler2D roughnessmap;
layout (binding = 4) uniform sampler2D ambeintocclusionmap;
layout (binding = 5) uniform sampler2D normalmap;



vec3 compute_bumps_via_normalmap(){
	
	vec3 bumps = texture(normalmap, uv_0).xyz;
	bumps = normalize(2.0f * bumps - 1.0f);
	
	vec3 detailed_normal = tbn * bumps;
	return normalize(detailed_normal);

}

void main (){

	// this bit of code to salience compiler since the features are not yet to be implemented 
	if ( use_metalic_map == 1 && use_specular_map == 1 && use_roughness_map == 1 && use_ao_map == 1 && use_ao_map == 1){
			 float ametalic = metalic;
			 float aspecular = specular;
			 float aroughness = roughness;
			 float aambeintocclusion = ambeintocclusion;
			 
	}
	vec3 light_dir = wordpos - lightposition;
	
	vec3 normalized_normal = normalize(normal_0);
	if (use_normal_map == 1) {
		normalized_normal = compute_bumps_via_normalmap();
	}

	float vertex_light_distance = length(light_dir);
	light_dir = normalize(light_dir);
	float attenuation = constant + linear * vertex_light_distance + quadratic * vertex_light_distance * vertex_light_distance;

	attenuation = 1.0f / attenuation;
	vec3  ambient_color  = lightcolor * ambient;
	float diffuse_factor = dot(normalized_normal, -light_dir);

	vec3 diffuse_color  = vec3(0.0f, 0.0f, 0.0f);
	vec3 specular_color = vec3(0.0f, 0.0f, 0.0f);

	float diffuse_intensity  = 5.5f;
	float specular_intensity = 8.0f;
	float specular_power     = 32.0f;

	if(diffuse_factor > 0.0f){
		diffuse_color = lightcolor * diffuse_intensity * diffuse_factor;
		vec3 view_ray = normalize(camera_world_location - wordpos);
		vec3 reflected_light = normalize(reflect(light_dir, normalized_normal));
		float specular_factor = dot(view_ray, reflected_light);
		if(specular_factor > 0.0f){
				specular_factor = pow(specular_factor, specular_power);
				specular_color = lightcolor * specular_intensity * specular_factor;
			}
	}

	vec3 total_light = (ambient_color + diffuse_color + specular_color) * attenuation; 
//	color = vec4(total_light, 1.0) * texture(diffuse, uv_0);
	if(use_albedo_map == 1)
		color = vec4(total_light, 1.0) * texture(albedomap, uv_0);
	else
		color = vec4(total_light, 1.0) * vec4(albedo, 1.0);
//	color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}