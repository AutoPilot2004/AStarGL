#version 430 core
#extension GL_ARB_bindless_texture : require

const vec2 quadLocalVertexTranslation[4] = vec2[](
									vec2(-0.5, -0.5),
									vec2( 0.5, -0.5),
									vec2( 0.5,  0.5),
									vec2(-0.5,  0.5));

const ivec2 indexToUV[4] = ivec2[](
					ivec2(0, 1),
					ivec2(2, 1),
					ivec2(2, 3),
					ivec2(0, 3));

struct Quad
{
	vec4     translationTexHandleIdx;
	vec4     rotationScaleRounding;
	vec4     uv;
	vec4     color;
};

layout(std430, binding = 0) readonly buffer QuadBuffer
{
	Quad quads[];
} quadBuffer;

uniform mat4 viewProj;

out vec2 scaledLocalCurrentCoord;
out vec2 halfExtent;
out float rounding;
out flat int texHandleIdx;
out vec2 uv;
out vec4 color;

void main()
{
	uint currentQuadIndex = gl_VertexID / 4;
	uint vertexOffsetFromCurrentQuad = gl_VertexID % 4;

	Quad currentQuad = quadBuffer.quads[currentQuadIndex];

	float rotation = radians(currentQuad.rotationScaleRounding.x);
	mat2 rotModel = mat2(
					vec2(cos(rotation), -sin(rotation)),
					vec2(sin(rotation), cos(rotation)));

	gl_Position = viewProj * vec4(currentQuad.translationTexHandleIdx.xy + rotModel * (currentQuad.rotationScaleRounding.yz * quadLocalVertexTranslation[vertexOffsetFromCurrentQuad]), currentQuad.translationTexHandleIdx.z, 1.0);

	scaledLocalCurrentCoord = quadLocalVertexTranslation[vertexOffsetFromCurrentQuad]*currentQuad.rotationScaleRounding.yz;
	halfExtent = currentQuad.rotationScaleRounding.yz / 2.0;
	rounding = max(min(currentQuad.rotationScaleRounding.w, 1.0), 0.0) * (min(currentQuad.rotationScaleRounding.y, currentQuad.rotationScaleRounding.z) / 2.0);
	texHandleIdx = int(currentQuad.translationTexHandleIdx.w);
	uv = vec2(currentQuad.uv[indexToUV[vertexOffsetFromCurrentQuad][0]], currentQuad.uv[indexToUV[vertexOffsetFromCurrentQuad][1]]);
	color = currentQuad.color;
}