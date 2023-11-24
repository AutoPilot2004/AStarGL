#version 430 core
#extension GL_ARB_bindless_texture : require

in vec2 scaledLocalCurrentCoord;
in vec2 halfExtent;
in float rounding;
in flat int texHandleIdx;
in vec2 uv;
in vec4 color;

layout(std430, binding = 1) readonly buffer TextureBuffer
{
	sampler2D textures[];
} textureBuffer;

out vec4 outColor;

float roundedBoxSDF() {
    return length(max(abs(scaledLocalCurrentCoord)-halfExtent+rounding,0.0))-rounding;
}

void main()
{
	if (roundedBoxSDF() > 0) discard;

	outColor = color * texture(textureBuffer.textures[texHandleIdx], uv);
}