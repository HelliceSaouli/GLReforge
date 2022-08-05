#version 450

layout(location = 0) in vec3 position;
layout(location = 0) in vec2 uv;

// out vec3 fragcolor;
out vec2 uv_0;

uniform mat4 transfrom_matrix;
uniform mat4 projection_matrix;
uniform mat4 camera_matrix;

void main(){
	gl_Position = projection_matrix * camera_matrix * transfrom_matrix * vec4(position, 1.0f);
	//	fragcolor = clamp(position, 0.0f, 1.0f);
	uv_0 = uv;
}