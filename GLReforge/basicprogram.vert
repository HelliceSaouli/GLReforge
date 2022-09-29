#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

// out vec3 fragcolor;
out vec2 uv_0;
out vec3 normal_0;
out vec3 wordpos;
out mat3 tbn;


uniform mat4 transfrom_matrix;
uniform mat4 projection_matrix;
uniform mat4 camera_matrix;

void main(){
	gl_Position = projection_matrix * camera_matrix * transfrom_matrix * vec4(position, 1.0f);
    wordpos = (transfrom_matrix * vec4(position, 1.0f)).xyz;
	uv_0 = uv;

	normal_0  = normalize(mat3(transfrom_matrix) * normal);
	vec3 tangent_0 = normalize(mat3(transfrom_matrix) * tangent);
	vec3 bitangent_0 =  normalize(mat3(transfrom_matrix) * bitangent);

	tbn = mat3(tangent_0, bitangent_0, normal_0);
}