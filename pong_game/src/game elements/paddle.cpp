#include "paddle.h"
#include <engine/renderer/renderer.h>
#include <engine/math/math.h>
#include <engine/time/time.h>
#include <engine/display/window.h>

paddle::paddle(f32 posx, f32 posy, f32 sizex, f32 sizey)
	: position(glm::vec2(posx, posy)), scale(glm::vec2(sizex, sizey))
{
	actual_scale = scale;
	move_scale = glm::vec2(scale.x - 10.0f, scale.y + 20.0f);
	paddle_color = WHITE;

	velocity = glm::vec2(0.0f);
	acceleration = glm::vec2(0.0f, 0.0f);
	drag = 0.97f;

	paddle_aabb = { position, scale * 0.5f };
	collided = false;
}

paddle::~paddle()
{
}

void paddle::update(Key upkey, Key downkey, f32 move_force)
{
	if (Input::isKeyPressed(upkey))
	{
		acceleration.y += move_force;

		scale.x = math::Lerpf(scale.x, move_scale.x, Time::m_deltaTime * 5.0f);
		scale.y = math::Lerpf(scale.y, move_scale.y, Time::m_deltaTime * 5.0f);
		if (collided)
			paddle_color = RED;
		else
			paddle_color = color{ 0.8f, 0.8f, 0.8f, 1.0f };
	}
	else if (Input::isKeyPressed(downkey))
	{
		acceleration.y -= move_force;

		scale.x = math::Lerpf(scale.x, move_scale.x, Time::m_deltaTime * 5.0f);
		scale.y = math::Lerpf(scale.y, move_scale.y, Time::m_deltaTime * 5.0f);
		
		if (collided)
			paddle_color = RED;
		else
			paddle_color = color{ 0.8f, 0.8f, 0.8f, 1.0f };
	}
	else
	{
		scale.x = math::Lerpf(scale.x, actual_scale.x, Time::m_deltaTime * 20.0f);
		scale.y = math::Lerpf(scale.y, actual_scale.y, Time::m_deltaTime * 20.0f);
		if(collided)
			paddle_color = RED;
		else
			paddle_color = color{ 0.5f, 0.5f, 0.5f, 1.0f };
	}

	// integration
	velocity += acceleration * Time::m_deltaTime;
	position += velocity * Time::m_deltaTime;

	velocity.y *= drag;

	acceleration = glm::vec2(0.0f);

	position.y = math::clampf(position.y, 25.0f + scale.y * 0.5f, window::getInstance()->getHeight() - 25.0f - scale.y * 0.5f);

	paddle_aabb = { position, scale * 0.5f };
}

void paddle::ai_update(bool is_moving, f32 ball_ypos, f32 move_speed)
{
	if (collided)
		paddle_color = RED;
	else
		paddle_color = color{ 0.5f, 0.5f, 0.5f, 1.0f };

	if (is_moving)
	{
		position.y = math::move_towards(position.y, ball_ypos, Time::m_deltaTime * move_speed);

		position.y = math::clampf(position.y, 25.0f + scale.y * 0.5f, window::getInstance()->getHeight() - 25.0f - scale.y * 0.5f);
	}
	// update collsion data
	paddle_aabb = { position, scale * 0.5f };
}

void paddle::draw()
{
	renderer::render_quad(position, scale, paddle_color);
}