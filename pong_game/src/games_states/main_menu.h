#pragma once

#include "game_state.h"
#include <engine/renderer/renderer.h>
#include <engine/physics/physics.h>
#include <game elements/paddle.h>
#include <game elements/ui_button.h>

class main_menu : public game_state
{
public:
	void init();
	void update();
	void render();
	void destroy();

private:
	texture* game_title;
	texture* game_info;

	glm::vec2 window_center;

	paddle* right_paddle;
	paddle* left_paddle;

	ui_button* play_button;
	ui_button* info_button;
	ui_button* quit_button;
	ui_button* return_button;
};