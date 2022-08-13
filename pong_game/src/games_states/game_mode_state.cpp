#include "game_mode_state.h"
#include <engine/display/window.h>
#include <engine/renderer/renderer.h>
#include <engine/input/input.h>
#include <games_states/game_play.h>
#include <games_states/ai_game_play.h>

void gameplay_mode::init()
{
	glm::vec2 window_center = glm::vec2(window::getInstance()->getWidth() * 0.5f, window::getInstance()->getHeight() * 0.5f);
	
	player_vs_player = new ui_button(glm::vec2(window_center.x + 200.0f, window_center.y), glm::vec2(200.0f, 80.0f));
	renderer::creat_texture(player_vs_player->tex, "assets/textures/playervsplayer.png");

	player_vs_ai = new ui_button(glm::vec2(window_center.x - 200.0f, window_center.y), glm::vec2(200.0f, 80.0f));
	renderer::creat_texture(player_vs_ai->tex, "assets/textures/playervsai.png");

	Input::show_cursor(false);
}

void gameplay_mode::update()
{
	player_vs_player->update();
	player_vs_ai->update();

	player_vs_player->selected = physicsWorld::point_vs_aabb(Input::getMousePos(), player_vs_player->collision_aabb);
	player_vs_ai->selected = physicsWorld::point_vs_aabb(Input::getMousePos(), player_vs_ai->collision_aabb);

	if (Input::isButtonDown(MouseButton::MouseButtonLeft))
	{
		if (player_vs_player->selected)
		{
			game_state_manger.set_state(new game_play());
		}
		else if (player_vs_ai->selected)
		{
			game_state_manger.set_state(new ai_game_play());
		}
	}
}

void gameplay_mode::render()
{
	renderer::render_quad(glm::vec2(0.0f), glm::vec2(window::getInstance()->getWidth(), window::getInstance()->getHeight()), BLACK);

	player_vs_player->draw();
	player_vs_ai->draw();

	renderer::render_quad(Input::getMousePos(), glm::vec2(10.0f), RED);
}

void gameplay_mode::destroy()
{
	delete player_vs_player;
	delete player_vs_ai;
}