#pragma once

#include <engine/defines.h>
#include <glm/glm.hpp>
#include <engine/physics/physics.h>

class ball
{
public:
	ball() = default;
	ball(f32 posx, f32 posy, f32 sizex, f32 sizey);
	~ball();

	void update(i32& r_score, i32& l_score);
	void draw();
	void reset_velocity();

	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 velocity;
	AABB ball_aabb;
};