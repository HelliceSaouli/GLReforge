#version 450

// in  vec3 fragcolor;
in  vec2 uv_0;
in  vec3 normal_0;

out vec4 color;

uniform vec3 ambient;
uniform sampler2D diffuse;

void main (){
	color = vec4(ambient, 1.0) * texture(diffuse, uv_0);
}