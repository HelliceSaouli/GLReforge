#version 450

layout(location = 0) in vec3 position;

out vec3 fragcolor;

uniform float scale;

void main(){
	gl_Position = vec4(position * scale, 1.0f);
	fragcolor = clamp(position, 0.0f, 1.0f);
}