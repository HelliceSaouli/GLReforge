#version 450

layout(location = 0) in vec3 position;

out vec3 fragcolor;

uniform mat4 transfrom_matrix;
uniform mat4 projection_matrix;

void main(){
	gl_Position = projection_matrix * transfrom_matrix * vec4(position, 1.0f);
	fragcolor = clamp(position, 0.0f, 1.0f);
}