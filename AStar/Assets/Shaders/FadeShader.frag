#version 430 core

in vec2 uv;

out vec4 outColor;

uniform float time;

void main()
{
	outColor = vec4(vec3(0.0), time);
}