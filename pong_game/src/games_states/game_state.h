#pragma once

class game_state
{
public:
	virtual void init() {};
	virtual void update() {};
	virtual void render() {};
	virtual void destroy() {};
};

class state_manger
{
public:
	state_manger();
	~state_manger();
	void set_state(game_state* s);
	void update();
	void render();
private:
	game_state* m_state;
};

extern state_manger game_state_manger;