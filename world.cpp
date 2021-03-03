#include "world.h"
#include <random>

World::World() {
	// creating map
	for (int i = 0; i < 10; ++i) {
		map[i] = "                       "; // 20 characters
	}

	// seed for generating random numbers
	srand(unsigned(time(0)));

	// spawning goal (X)
	goal.set_x(rand() % 10);
	goal.set_y(rand() % 20);
	map[goal.get_x()][goal.get_y()] = goal.sign;

	// spawning player (G)
	player.set_x(rand() % 10);
	player.set_y(rand() % 20);
	map[player.get_x()][player.get_y()] = player.sign;

	// spawning enemy (T)
	enemy.set_x(rand() % 10);
	enemy.set_y(rand() % 20);
	map[enemy.get_x()][enemy.get_y()] = enemy.sign;
}

void World::new_level_spawns() {
	// respawn goal
	map[goal.get_x()][goal.get_y()] = empty_sign;
	goal.set_x(rand() % 10);
	goal.set_y(rand() % 20);
	map[goal.get_x()][goal.get_y()] = goal.sign;

	// respawn enemy
	map[enemy.get_x()][enemy.get_y()] = empty_sign;
	enemy.set_x(rand() % 10);
	enemy.set_y(rand() % 20);
	map[enemy.get_x()][enemy.get_y()] = enemy.sign;

	// respawn player
	map[player.get_x()][player.get_y()] = empty_sign;
	player.set_x(rand() % 10);
	player.set_y(rand() % 20);
	map[player.get_x()][player.get_y()] = player.sign;
}

void World::new_level() {
	// just int to display
	++level;
}

void World::print_map() {
	std::cout << "\tLevel <" << level << ">\n\n";
	for (int i = 0; i < map_size; ++i) {
		std::cout << map[i] << '\n';
	}
	map[goal.get_x()][goal.get_y()] = goal.sign;
}

bool World::change_cell(int x, int y, char& c) {
	if (x > map_size || y > map_size * 2) {
		return false;
	}
	map[x][y] = c;
	return true;
}

char empty_cell = '.';
void World::move_player(char direction) {
	if (direction == 'w') { // up
		if (player.get_x() == 0) return;
		change_cell(player.get_x(), player.get_y(), empty_cell);
		player.set_x(player.get_x() - 1);
		change_cell(player.get_x(), player.get_y(), player.sign);
	}
	else if (direction == 'a') { // left
		if (player.get_y() == 0) return;
		change_cell(player.get_x(), player.get_y(), empty_cell);
		player.set_y(player.get_y() - 1);
		change_cell(player.get_x(), player.get_y(), player.sign);
	}
	else if (direction == 's') { // down
		if (player.get_x() == 9) return;
		change_cell(player.get_x(), player.get_y(), empty_cell);
		player.set_x(player.get_x() + 1);
		change_cell(player.get_x(), player.get_y(), player.sign);
	}
	else if (direction == 'd') { // right
		if (player.get_y() == 19) return;
		change_cell(player.get_x(), player.get_y(), empty_cell);
		player.set_y(player.get_y() + 1);
		change_cell(player.get_x(), player.get_y(), player.sign);
	}
}

Player World::get_player() {
	return player;
}

bool World::is_end() {
	if (player.get_x() == goal.get_x() &&
		player.get_y() == goal.get_y()) {
		return true;
	}
	return false;
}

bool World::is_dead() {
	if (enemy.get_x() == player.get_x() &&
		enemy.get_y() == player.get_y())
		return true;
	return false;
}

// enemy is moving randomly
void World::move_enemy() {
	
	srand(unsigned(time(0)));
	
	int move = rand() % 8 + 1;
	// 1 - left, 2 - down, 3 - up, 4 - right
	// 5 - left+up, 6 - left+down
	// 7 - right+up, 8 - right+down
	if (move == 1) { // left
		if (enemy.get_y() == 0) return;
		change_cell(enemy.get_x(), enemy.get_y(), empty_cell);
		enemy.set_y(enemy.get_y() - 1);
		change_cell(enemy.get_x(), enemy.get_y(), enemy.sign);
	}
	else if (move == 2) { // down
		if (enemy.get_x() == 9) return;
		change_cell(enemy.get_x(), enemy.get_y(), empty_cell);
		enemy.set_x(enemy.get_x() + 1);
		change_cell(enemy.get_x(), enemy.get_y(), enemy.sign);
	}
	else if (move == 3) { // up
		if (enemy.get_x() == 0) return;
		change_cell(enemy.get_x(), enemy.get_y(), empty_cell);
		enemy.set_x(enemy.get_x() - 1);
		change_cell(enemy.get_x(), enemy.get_y(), enemy.sign);
	}
	else if (move == 4) { // right
		if (enemy.get_y() == 19) return;
		change_cell(enemy.get_x(), enemy.get_y(), empty_cell);
		enemy.set_y(enemy.get_y() + 1);
		change_cell(enemy.get_x(), enemy.get_y(), enemy.sign);
	}
	else if (move == 5) { // left+up
		if (enemy.get_y() == 0 || enemy.get_x() == 0) return;
		change_cell(enemy.get_x(), enemy.get_y(), empty_cell);
		enemy.set_y(enemy.get_y() - 1);
		enemy.set_x(enemy.get_x() - 1);
		change_cell(enemy.get_x(), enemy.get_y(), enemy.sign);
	}
	else if (move == 6) { // left+down
		if (enemy.get_y() == 0 || enemy.get_x() == 9) return;
		change_cell(enemy.get_x(), enemy.get_y(), empty_cell);
		enemy.set_y(enemy.get_y() - 1);
		enemy.set_x(enemy.get_x() + 1);
		change_cell(enemy.get_x(), enemy.get_y(), enemy.sign);
	}
	else if (move == 7) { // right+up
		if (enemy.get_y() == 19 || enemy.get_x() == 0) return;
		change_cell(enemy.get_x(), enemy.get_y(), empty_cell);
		enemy.set_y(enemy.get_y() + 1);
		enemy.set_x(enemy.get_x() - 1);
		change_cell(enemy.get_x(), enemy.get_y(), enemy.sign);
	}
	else if (move == 8) { // right+down
		if (enemy.get_y() == 19 || enemy.get_x() == 9) return;
		change_cell(enemy.get_x(), enemy.get_y(), empty_cell);
		enemy.set_y(enemy.get_y() + 1);
		enemy.set_x(enemy.get_x() + 1);
		change_cell(enemy.get_x(), enemy.get_y(), enemy.sign);
	}
}

int World::get_level() {
	return level;
}
