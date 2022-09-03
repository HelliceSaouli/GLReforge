#version 450

// in  vec3 fragcolor;
in  vec2 uv_0;
in  vec3 normal_0;
in  vec3 wordpos;

out vec4 color;

uniform vec3 ambient;
uniform vec3 sunlightcolor;
uniform vec3 sunlightdirection;
uniform vec3 camera_world_location;


uniform sampler2D albedomap;
uniform sampler2D metallicmap;
uniform sampler2D specularmap;
uniform sampler2D roughnessmap;
uniform sampler2D aomap;
uniform sampler2D normalmap;

void main (){


	color = texture(albedomap, uv_0);
}