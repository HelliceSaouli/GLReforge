#version 450

// in  vec3 fragcolor;
in  vec2 uv_0;

out vec4 color;

uniform sampler2D diffuse;

void main (){
	color = texture(diffuse, uv_0);
}