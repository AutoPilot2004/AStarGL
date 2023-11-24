#pragma once
#include "Graphics/Texture.h"
#include "Math/Transform2D.h"
#include "Graphics/Shader.h"

namespace engine
{
	struct Shape
	{
		Transform2DBasic transform;
		Texture texture;
		glm::vec4 color{ 1.0f };
		Shader* shader = nullptr;

		//TODO: IMPLEMENT TEXTURE2D
		//Texture2D texture;

	protected:
		Shape() = default;
		Shape(const Transform2DBasic& transform, const glm::vec4& color, Shader* shader) : transform(transform), color(color), shader(shader) {}
	};

	struct Rect : public Shape
	{
		Rect() = default;
		Rect(const Transform2DBasic& transform, const glm::vec4& color, Shader* shader, float rounding) : Shape(transform, color, shader), rounding(rounding) {}

		float rounding = 0.0f;
	};

	struct Circle : public Shape
	{
		float radius = 1.0f;
	};
}