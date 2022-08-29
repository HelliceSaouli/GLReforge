#version 450

// in  vec3 fragcolor;
in  vec2 uv_0;
in  vec3 normal_0;
in  vec3 wordpos;

out vec4 color;

uniform vec3 ambient;
uniform vec3 lightcolor;
uniform vec3 lightposition;
uniform vec3 camera_world_location;

uniform float constant;
uniform float linear;
uniform float quadratic;

uniform sampler2D diffuse;

void main (){

	vec3 light_dir = wordpos - lightposition;
	vec3 normalized_normal = normalize(normal_0);
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
	color = texture(diffuse, uv_0);
//	color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}