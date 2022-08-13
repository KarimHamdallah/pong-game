#include "game_play.h"
#include <engine/display/window.h>
#include <engine/renderer/renderer.h>
#include <engine/time/time.h>
#include <engine/logger/asserts.h>

void game_play::init()
{
	// window info
	window_width = (f32)window::getInstance()->getWidth();
	window_height = (f32)window::getInstance()->getHeight();
	window_center = glm::vec2(window_width * 0.5f, window_height * 0.5f);

	// paddle init
	f32 offset = 40.0f;
	right_player = new paddle(window_width - offset, window_center.y, 30.0f, 110.0f);
	left_player = new paddle(offset, window_center.y, 30.0f, 110.0f);

	// ball init
	Ball = new ball(window_center.x, window_center.y, 10.0f, 10.0f);

	r_score = l_score = 0;
	Input::show_cursor(false);
}

void game_play::update()
{
	right_player->update(Key::Up, Key::Down, 1500.0f);
	left_player->update(Key::W, Key::S, 1500.0f);
	Ball->update(r_score, l_score);

	if (physicsWorld::aabb_vs_aabb(right_player->paddle_aabb, Ball->ball_aabb))
	{
		Ball->position = glm::vec2(right_player->position.x - right_player->paddle_aabb.half_scale.x - Ball->ball_aabb.half_scale.x - 5.0f, Ball->position.y);
		Ball->velocity += right_player->velocity * Time::m_deltaTime;
		Ball->velocity.x *= -1.0f;
		right_player->collided = true;
	}
	else if (physicsWorld::aabb_vs_aabb(left_player->paddle_aabb, Ball->ball_aabb))
	{
		Ball->position = glm::vec2(left_player->position.x + left_player->paddle_aabb.half_scale.x + Ball->ball_aabb.half_scale.x + 5.0f, Ball->position.y);
		Ball->velocity += right_player->velocity * Time::m_deltaTime;
		Ball->velocity.x *= -1.0f;
		left_player->collided = true;
	}
	else
	{
		right_player->collided = false;
		left_player->collided = false;
	}
}

void game_play::render()
{
	// back ground
	renderer::render_quad(window_center, glm::vec2(window_width - 20, window_height - 50), RGBA_COLOR(46.0f, 45.0f, 44.0f, 255.0f));

	// paddles
	right_player->draw();
	left_player->draw();
	Ball->draw();
}

void game_play::destroy()
{
	delete right_player;
	delete left_player;
	delete Ball;
}