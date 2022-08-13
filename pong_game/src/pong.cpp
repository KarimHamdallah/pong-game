#include <engine/display/window.h>
#include <engine/renderer/renderer.h>
#include <engine/logger/Logger.h>
#include <engine/input/input.h>
#include <engine/time/Time.h>
#include "games_states/main_menu.h"

state_manger game_state_manger;

int main(int argc, char* argv[])
{
	// setup logger system
	Log::init();

	// setup window system
	std::shared_ptr<window> game_window = std::make_shared<window>("pong game", 800, 600, window_type::window_non_resizable);

	// setup input system
	InputSystem& inputsystem = InputSystem::getInstance();
	inputsystem.init(game_window);

	// setup time system
	Time::time_init(60);

	// setup renderer sysytem
	renderer::renderer_init();


	// TODO:: REMOVE
	// start
	game_state_manger.set_state(new main_menu());


	while (!game_window->shouldClose())
	{
		Time::time_update();
		game_window->update();

		// input
		if (Input::isKeyPressed(Key::EscapeKey))
			game_window->setShouldClose(true);


		// TODO:: REMOVE
		// update
		game_state_manger.update();

		// renderering
		renderer::renderer_begin(BLACK);
		// TODO:: REMOVE
		game_state_manger.render();
		renderer::renderer_end(game_window->getRenderingWindow());

		Time::time_update_late();
	}

	return 0;
}