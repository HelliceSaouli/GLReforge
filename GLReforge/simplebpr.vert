#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

// out vec3 fragcolor;
out vec2 uv_0;
out vec3 normal_0;
out vec3 wordpos;


uniform mat4 transfrom_matrix;
uniform mat4 projection_matrix;
uniform mat4 camera_matrix;



void main(){
	gl_Position = projection_matrix * camera_matrix * transfrom_matrix * vec4(position, 1.0f);
    wordpos = (transfrom_matrix * vec4(position, 1.0f)).xyz;
	uv_0 = uv;
	normal_0 = inverse(transpose(mat3(transfrom_matrix))) * normal;
}