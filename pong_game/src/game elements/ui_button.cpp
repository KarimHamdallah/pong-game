#include "ui_button.h"
#include <engine/math/math.h>
#include <engine/time/time.h>

ui_button::ui_button(glm::vec2 pos, glm::vec2 size, color havorcolor, bool is_selected)
	: position(pos), scale(size), selected(is_selected), havor_color(havorcolor)
{
	havor_scale = scale * 1.5f;
	non_havor_scale = scale;
	tex = new texture();
	collision_aabb = { position, scale * 0.5f };
}

ui_button::~ui_button()
{
	if(tex->id != 0)
		renderer::free_texture(tex);
	if(tex)
		delete tex;
}

void ui_button::update()
{
	if (selected)
	{
		// lerp to havor scale
		scale.x = math::Lerpf(scale.x, havor_scale.x, Time::m_deltaTime * 2.0f);
		scale.y = math::Lerpf(scale.y, havor_scale.y, Time::m_deltaTime * 2.0f);
	}
	else
	{
		// lerp to unhavor scale
		scale.x = math::Lerpf(scale.x, non_havor_scale.x, Time::m_deltaTime * 2.0f);
		scale.y = math::Lerpf(scale.y, non_havor_scale.y, Time::m_deltaTime * 2.0f);
	}

	// update collsion scale
	collision_aabb.half_scale = scale * 0.5f;
}

void ui_button::draw()
{
	if (selected)
		renderer::render_sprite(tex, position, scale, havor_color);
	else
		renderer::render_sprite(tex, position, scale);
}