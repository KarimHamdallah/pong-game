#include "main_menu.h"
#include <engine/display/window.h>
#include <engine/time/time.h>
#include <engine/logger/Logger.h>
#include <engine/math/math.h>
#include <engine/physics/physics.h>
#include <engine/input/input.h>
#include "game_mode_state.h"

static f32 window_width;
static f32 window_height;
bool show_info_message = false;

void main_menu::init()
{
	// window info
	window_width = (f32)window::getInstance()->getWidth();
	window_height = (f32)window::getInstance()->getHeight();
	window_center = glm::vec2(window_width * 0.5f, window_height * 0.5f);

	// game title
	game_title = new texture();
	renderer::creat_texture(game_title, "assets/textures/title.png");
	
	// game info message
	game_info = new texture();
	renderer::creat_texture(game_info, "assets/textures/info_text.png");

	// paddles
	right_paddle = new paddle(window_width - 40, window_center.y, 20.0f, 100.0f);
	left_paddle = new paddle(40, window_center.y, 20.0f, 100.0f);

	// ui init
	play_button = new ui_button(glm::vec2(window_center.x, window_center.y), glm::vec2(150.0f, 40.0f));
	renderer::creat_texture(play_button->tex, "assets/textures/start.png");

	info_button = new ui_button(glm::vec2(window_center.x, window_center.y - 100.0f), glm::vec2(150.0f, 40.0f), color{0.0f,0.0f,0.8f,1.0f});
	renderer::creat_texture(info_button->tex, "assets/textures/info.png");

	quit_button = new ui_button(glm::vec2(window_center.x, window_center.y - 200.0f), glm::vec2(150.0f, 40.0f), color{ 0.8f,0.0f,0.0f,1.0f });
	renderer::creat_texture(quit_button->tex, "assets/textures/quit.png");

	return_button = new ui_button(glm::vec2(window_center.x, window_center.y + 250.0f), glm::vec2(150.0f, 40.0f));
	renderer::creat_texture(return_button->tex, "assets/textures/return.png");

	Input::show_cursor(false);
}

void main_menu::update()
{
	// move paddles
	right_paddle->position.y += math::sinf(Time::get_time());
	left_paddle->position.y = window_height - right_paddle->position.y;


	// ui update
	glm::vec2 cursor_position = Input::getMousePos();
	
	if (!show_info_message)
	{
		// check if selected
		play_button->selected = physicsWorld::point_vs_aabb(cursor_position, play_button->collision_aabb);
		info_button->selected = physicsWorld::point_vs_aabb(cursor_position, info_button->collision_aabb);
		quit_button->selected = physicsWorld::point_vs_aabb(cursor_position, quit_button->collision_aabb);

		// update buttons scale and collsion scale
		play_button->update();
		info_button->update();
		quit_button->update();

	}
	else
	{
		// check if selected
		return_button->selected = physicsWorld::point_vs_aabb(cursor_position, return_button->collision_aabb);

		// update button scale and collsion scale
		return_button->update();

		// return if clicked
		if (return_button->selected && Input::isButtonDown(MouseButton::MouseButtonLeft))
		{
			show_info_message = false;
		}
	}

	// clicked action
	if (Input::isButtonDown(MouseButton::MouseButtonLeft))
	{
		window::getInstance()->setShouldClose(quit_button->selected);

		if (info_button->selected)
			show_info_message = true;
		else
			show_info_message = false;

		if (play_button->selected)
			game_state_manger.set_state(new gameplay_mode());
	}
}

void main_menu::render()
{
	// paddles
	renderer::render_quad(right_paddle->position, right_paddle->scale, WHITE);
	renderer::render_quad(left_paddle->position, left_paddle->scale, WHITE);
	
	// game title
	renderer::render_sprite(game_title, glm::vec2(window_center.x, window_center.y + 120), glm::vec2(300, 200));

	// ui draw
	play_button->draw();
	info_button->draw();
	quit_button->draw();

	if (show_info_message)
	{
		// shadow layer
		renderer::render_quad(window_center, glm::vec2(window_width, window_height), color{ 0.0f,0.0f,0.0f,0.8f });
		renderer::render_sprite(game_info, window_center, glm::vec2(400.0f));
		return_button->draw();
	}

	// cusor quad
	renderer::render_quad(Input::getMousePos(), glm::vec2(10.0f), show_info_message ? BLUE : WHITE);
}

void main_menu::destroy()
{
	renderer::free_texture(game_title);
	delete game_title;
	delete game_info;

	delete right_paddle;
	delete left_paddle;

	delete play_button;
	delete info_button;
	delete quit_button;
	delete return_button;
}