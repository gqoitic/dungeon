#include <chrono>
#include <thread>
#include <windows.h>
#include "game.h"

using namespace std::chrono_literals;
void little_pause() {
	std::this_thread::sleep_for(200ms);
}

bool game() {
	World world;

	while (true) {
		// print map
		world.print_map();

		bool player_moved = false;

		// player move
		if (GetKeyState('W') < 0) {
			world.move_player('w');
			little_pause();
			player_moved = true;
		}
		else if (GetKeyState('A') < 0) {
			world.move_player('a');
			little_pause();
			player_moved = true;
		}
		else if (GetKeyState('S') < 0) {
			world.move_player('s');
			little_pause();
			player_moved = true;
		}
		else if (GetKeyState('D') < 0) {
			world.move_player('d');
			little_pause();
			player_moved = true;
		}

		// check if player dead after player's move
		if (world.is_dead()) {
			std::cout << "You died! Level: " << world.get_level() << '\n';
			break;
		}

		// enemy move
		if (player_moved)
			world.move_enemy();

		// check if player dead after enemy's move
		if (world.is_dead()) {
			std::cout << "You died! Level: " << world.get_level() << '\n';
			break;
		}

		// for updating
		system("cls");

		// new level if end
		if (world.is_end()) {
			world.new_level_spawns();
			world.new_level();
		}
	}

	std::cout << "\n<Game over!>\n";

	return false;
}
