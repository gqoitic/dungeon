#pragma once

#include <string>
#include <iostream>
#include "player.h"
#include "enemy.h"
#include "goal.h"

class World {
private:
	std::string map[10];
	int map_size = sizeof(map) / sizeof(std::string);
	Player player;
	Enemy enemy;
	Goal goal;
	int level = 1;
	char empty_sign = '.';

public:
	World();

	void print_map();
	bool change_cell(int x, int y, char& c);
	void new_level_spawns();
	void new_level();
	int get_level();

	// player methods
	void move_player(char direction);
	Player get_player();
	bool is_end();
	bool is_dead();

	// enemy methods
	void move_enemy();
};
