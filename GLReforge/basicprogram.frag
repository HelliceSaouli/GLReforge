#version 450

// in  vec3 fragcolor;
in  vec2 uv_0;
in  vec3 normal_0;
in  vec3 light_dir;
in float vertex_light_distance;

out vec4 color;

uniform vec3 ambient;
uniform vec3 lightcolor;


uniform float constant;
uniform float linear;
uniform float quadratic;

uniform sampler2D diffuse;

void main (){

	float attenuation = constant + linear * vertex_light_distance + quadratic * vertex_light_distance * vertex_light_distance;
	attenuation = 1.0f / attenuation;
	vec3  ambient_color  = lightcolor * ambient;
	float diffuse_factor = dot(normal_0, -light_dir);

	vec3 diffuse_color = vec3(0.0f, 0.0f, 0.0f);
	vec3 diffuse_intensity = vec3(10.0f, 10.0f, 10.0f);

	if(diffuse_factor > 0.0f){
		diffuse_color = lightcolor * diffuse_intensity * diffuse_factor;
	}
	vec3 total_light = (ambient_color + diffuse_color ) * attenuation; 
	color = vec4(total_light, 1.0) * texture(diffuse, uv_0);
}