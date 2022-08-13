#include "ball.h"
#include <engine/renderer/renderer.h>
#include <engine/display/window.h>
#include <engine/input/input.h>
#include <engine/math/math.h>

ball::ball(f32 posx, f32 posy, f32 sizex, f32 sizey)
	: position(posx, posy), scale(sizex, sizey)
{
	velocity = glm::vec2(1.0f, 0.0f);
	velocity *= 5.0f;
	ball_aabb = { position, scale * 0.5f };
	LOG_INFO("left player score = 0, right player score = 0");
}

ball::~ball()
{
}

void ball::update(i32& r_score, i32& l_score)
{
	position += velocity;

	f32 bordery = 20.0f;

	f32 offset = 5.0f;

	if (position.y + scale.y * 0.5f > window::getInstance()->getHeight() - bordery)
	{
		position.y = window::getInstance()->getHeight() - scale.y * 0.5f - offset - bordery;
		velocity.y *= -1.0f;
	}
	if (position.y - scale.y * 0.5f < bordery)
	{
		position.y = scale.y * 0.5f + offset + bordery;
		velocity.y *= -1.0f;
	}

	ball_aabb.position = position;

	if (position.x + ball_aabb.half_scale.x < 0.0f)
	{
		reset_velocity();
		r_score++;
		LOG_INFO("left player score = {0}, right player score = {1}", l_score, r_score);
	}
	else if (position.x - ball_aabb.half_scale.x > window::getInstance()->getWidth())
	{
		reset_velocity();
		l_score++;
		LOG_INFO("left player score = {0}, right player score = {1}", l_score, r_score);
	}

	velocity.x = math::clampf(velocity.x, -12.0f, 12.0f);
	velocity.y = math::clampf(velocity.y, -12.0f, 12.0f);
}

void ball::draw()
{
	renderer::render_quad(position, scale, RED);
}

void ball::reset_velocity()
{
	glm::vec2 directions[4]
	{
	glm::vec2(1.0f, 1.0f),
	glm::vec2(1.0f, -1.0f),
	glm::vec2(-1.0f, 1.0f),
	glm::vec2(-1.0f, -1.0f)
	};
	int choise = rand() % 4;
	
	velocity = directions[choise];
	glm::normalize(velocity);
	
	velocity *= math::random(3, 5);
	position = glm::vec2(window::getInstance()->getWidth() * 0.5f, window::getInstance()->getHeight() * 0.5f);
}