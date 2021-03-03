#pragma once

class Unit {
public:
	char sign = 'U';
	int x = 0;
	int y = 0;

	Unit();

	int get_x();
	int get_y();
	void set_x(int x);
	void set_y(int y);
};
