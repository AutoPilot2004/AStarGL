#version 430 core

out vec2 uv;

void main()
{
	int x = 1 - gl_VertexID&1;
	int y = 1 - gl_VertexID&2;

	gl_Position = vec4(3.0 - x*4.0, 3.0 - y*4.0, 0.0, 1.0);

	uv = vec2(2.0 - x*2.0, 2.0 - y*2.0);
}