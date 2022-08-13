#pragma once
#include <game elements/ui_button.h>
#include "game_state.h"

class gameplay_mode : public game_state
{
public:
	void init();
	void update();
	void render();
	void destroy();

	ui_button* player_vs_player;
	ui_button* player_vs_ai;
};