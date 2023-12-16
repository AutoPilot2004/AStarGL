#pragma once

#include "Management/Events/Dispatcher.h"
#include "Management/Events/Input.h"

#include "Management/Textures/TextureManager.h"
#include "Management/Cameras/CameraManager.h"

#include "Renderer/Renderer2D.h"

namespace engine
{
	struct ApplicationContext
	{
		TextureManager textureManager;
		Renderer2D     renderer2D;
	};

	struct SceneContext
	{
		Dispatcher*     dispatcher     = nullptr;
		const Input*    input          = nullptr;
		TextureManager* textureManager = nullptr;
		Renderer2D*     renderer2D     = nullptr;
	};
}