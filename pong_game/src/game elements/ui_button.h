#pragma once
#include <engine/renderer/renderer.h>
#include <engine/physics/physics.h>

#include <glm/glm.hpp>

class ui_button
{
public:
	ui_button() = default;
	ui_button(glm::vec2 pos, glm::vec2 size, color havorcolor = color{ 0.0f, 0.8f, 0.0f, 1.0f }, bool is_selected = false);
	~ui_button();



	void update();
	void draw();
	
	glm::vec2 position;
	glm::vec2 scale;
	bool selected;
	texture* tex;
	AABB collision_aabb;

private:
	glm::vec2 havor_scale;
	glm::vec2 non_havor_scale;
	color havor_color;
};