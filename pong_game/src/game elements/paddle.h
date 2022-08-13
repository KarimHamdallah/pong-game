#pragma once

#include <engine/defines.h>
#include <glm/glm.hpp>
#include <engine/input/input.h>
#include <engine/physics/physics.h>


class paddle
{
public:
	paddle() = default;
	paddle(f32 posx, f32 posy, f32 sizex, f32 sizey);
	~paddle();

	void update(Key upkey, Key downkey, f32 move_force);
	// AI update
	void ai_update(bool is_moving, f32 ball_ypos, f32 move_speed);
	void draw();

	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 move_scale;
	glm::vec2 actual_scale;
	color paddle_color;

	glm::vec2 velocity;
	glm::vec2 acceleration;
	f32 drag;
	AABB paddle_aabb;
	bool collided;
};