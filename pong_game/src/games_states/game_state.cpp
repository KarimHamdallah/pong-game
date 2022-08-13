#include "game_state.h"

state_manger::state_manger()
{
	m_state = nullptr;
}

state_manger::~state_manger()
{
	if (m_state != nullptr) { m_state->destroy(); }
	delete m_state;
}

void state_manger::set_state(game_state * s)
{
	if (m_state) { m_state->destroy(); }
	delete m_state;
	m_state = s;
	if (m_state) { m_state->init(); }
}

void state_manger::update()
{
	if (m_state) { m_state->update(); }
}

void state_manger::render()
{
	if (m_state) { m_state->render(); }
}