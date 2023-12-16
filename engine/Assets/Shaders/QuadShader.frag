#version 430 core

in vec2 scaledLocalCurrentCoord;
in vec2 halfExtent;
in float rounding;
in flat int texHandleIdx;
in vec2 uv;
in vec4 color;

out vec4 outColor;

float roundedBoxSDF() {
    return length(max(abs(scaledLocalCurrentCoord)-halfExtent+rounding,0.0))-rounding;
}

void main()
{
	if (roundedBoxSDF() > 0) discard;

	outColor = color;
}