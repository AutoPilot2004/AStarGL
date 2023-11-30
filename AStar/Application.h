#pragma once
#include <engine/Application.h>


class Application : public engine::Application
{
public:
	void init() override;
	void mainLoop() override;

private:
};