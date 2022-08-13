#pragma once

#include <engine/defines.h>
#include "game_state.h"
#include <glm/glm.hpp>
#include <game elements/paddle.h>
#include <game elements/ball.h>

class ai_game_play : public game_state
{
public:
	void init();
	void update();
	void render();
	void destroy();



	f32 window_width;
	f32 window_height;
	glm::vec2 window_center;

	// paddles
	paddle* right_player;
	paddle* ai_player;
	ball* Ball;
	int r_score, l_score;
};