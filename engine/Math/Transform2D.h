#pragma once
#include "Transform.h"

namespace engine
{
/*class*/struct Transform2DBasic /* : public Transform */
		{
			glm::vec3 translation{ 0.0f, 0.0f, 0.0f };
			float     rotation{ 0.0f };
			glm::vec2 scale{ 1.0f, 1.0f };
		};
}

namespace engine
{
	class Transform2DAdvanced : public Transform, private Transform2DBasic
	{
	public:
		//Setters
		inline void setTranslation(const glm::vec3& translation)  { this->translation = translation;     m_translationDirty = true; }
		inline void setRotation(float rotationInDegrees)          { this->rotation = rotationInDegrees;  m_rotationDirty = true; }
		inline void setScale(const glm::vec2& scale)              { this->scale = scale;                 m_scaleDirty = true; }

		//Getters
		inline const glm::vec3& getTranslation()      const { return translation; }
		inline float            getRotation()         const { return rotation; }
		inline const glm::vec2& getScale()            const { return scale; }

	private:
		void updateTransformMatrix() override;

	private:
	};
}