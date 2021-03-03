#include "unit.h"
#include <random>
#include <iostream>

Unit::Unit() {}

int Unit::get_x() {
	return x;
}

int Unit::get_y() {
	return y;
}

void Unit::set_x(int x) {
	this->x = x;
}

void Unit::set_y(int y) {
	this->y = y;
}
