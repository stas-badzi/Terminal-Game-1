#include "Position.hpp"

#include <cmath>

using namespace std;

Position::Position(const double& init_x, const double& init_y, const double& init_z, const double & init_dx, const double& init_dy) {
	x = init_x;
	y = init_y;
	z = init_z;
	dx = init_dx;
	dy = init_dy;
}

void Position::operator=(Position position) {
	x = position.x;
	y = position.y;
	z = position.z;
	dx = position.dx;
	dy = position.dy;
}

void Position::operator+=(Position position) {
	x += position.x;
	y += position.y;
	z += position.z;
	dx += position.dx;
	dy += position.dy;
}

void Position::operator-=(Position position) {
	x -= position.x;
	y -= position.y;
	z -= position.z;
	dx -= position.dx;
	dy -= position.dy;
}

Position Position::Floor(Position position) {
	double posx = position.x;
	double posy = position.y;
	double posz = position.z;
	double posdx = position.dx;
	double posdy = position.dy;

	posx = floor(posx);
	posy = floor(posy);
	posz = floor(posz);
	posdx = floor(posdx);
	posdy = floor(posdy);

	return Position(posx,posy,posz,posdx,posdy);
}

Position Position::Abs(Position position) {
	double posx = position.x;
	double posy = position.y;
	double posz = position.z;
	double posdx = position.dx;
	double posdy = position.dy;

	posx = abs(posx);
	posy = abs(posy);
	posz = abs(posz);
	posdx = abs(posdx);
	posdy = abs(posdy);

	return Position(posx, posy, posz, posdx, posdy);
}

bool Position::operator>(Position position) const {
	bool out = true;
	out = out && x > position.x;
	out = out && y > position.y;
	out = out && z > position.z;
	out = out && dx > position.dx;
	out = out && dy > position.dy;
	return out;
}

bool Position::operator<(Position position) const {
	bool out = true;
	out = out && x < position.x;
	out = out && y < position.y;
	out = out && z < position.z;
	out = out && dx < position.dx;
	out = out && dy < position.dy;
	return out;
}

bool Position::operator==(Position position) const {
	bool out = true;
	out = out && x == position.x;
	out = out && y == position.y;
	out = out && z == position.z;
	out = out && dx == position.dx;
	out = out && dy == position.dy;
	return out;
}

bool Position::operator!=(Position position) const {
	return !( (*this) == position );
}

bool Position::operator>=(Position position) const {
	bool out = true;
	out = out && x >= position.x;
	out = out && y >= position.y;
	out = out && z >= position.z;
	out = out && dx >= position.dx;
	out = out && dy >= position.dy;
	return out;
}

bool Position::operator<=(Position position) const {
	bool out;
	out = x <= position.x;
	out = out && y <= position.y;
	out = out && z <= position.z;
	out = out && dx <= position.dx;
	out = out && dy <= position.dy;
	return out;
}

Position Position::operator+(Position position) const {

	double posx = x + position.x;
	double posy = y + position.y;
	double posz = z + position.z;
	double posdx = dx + position.dx;
	double posdy = dy + position.dy;

	return Position(posx, posy, posz, posdx, posdy);
}

Position Position::operator-(Position position) const {

	double posx = x - position.x;
	double posy = y - position.y;
	double posz = z - position.z;
	double posdx = dx - position.dx;
	double posdy = dy - position.dy;

	return Position(posx, posy, posz, posdx, posdy);
}

Position Position::operator%(Position position) const {
	double posx = (position.x != 0) ? x - (floor(x / position.x) * position.x) : x;
	double posy = (position.y != 0) ? y - (floor(y / position.y) * position.y) : y;
	double posz = (position.z != 0) ? z - (floor(z / position.z) * position.z) : z;
	double posdx = (position.dx != 0) ? dx - (floor(dx / position.dx) * position.dx) : dx;
	double posdy = (position.dy != 0) ? dy - (floor(dy / position.dy) * position.dy) : dy;

	return Position(posx, posy, posz, posdx, posdy);
}

Position Position::operator*(Position position) const {
	double posx = x * position.x;
	double posy = y * position.y;
	double posz = z * position.z;
	double posdx = dx * position.dx;
	double posdy = dy * position.dy;

	return Position(posx, posy, posz, posdx, posdy);
}

Position Position::operator/(Position position) const {
	double posx = (position.x != 0) ? x / position.x : x;
	double posy = (position.y != 0) ? y / position.y : y;
	double posz = (position.z != 0) ? z / position.z : z;
	double posdx = (position.dx != 0) ? dx / position.dx : dx;
	double posdy = (position.dy != 0) ? dy / position.dy : dy;

	return Position(posx, posy, posz, posdx, posdy);
}

void Position::operator%=(Position position) {
	x = (position.x != 0) ? x - (floor(x / position.x) * position.x) : x;
	y = (position.y != 0) ? y - (floor(y / position.y) * position.y) : y;
	z = (position.z != 0) ? z - (floor(z / position.z) * position.z) : z;
	dx = (position.dx != 0) ? dx - (floor(dx / position.dx) * position.dx) : dx;
	dy = (position.dy != 0) ? dy - (floor(dy / position.dy) * position.dy) : dy;

	return (void)NULL;
}

void Position::operator*=(Position position) {
	x *= position.x;
	y *= position.y;
	z *= position.z;
	dx *= position.dx;
	dy *= position.dy;
}

void Position::operator/=(Position position) {
	x = (x != 0) ? x / position.x : x;
	y = (y != 0) ? y / position.y : y;
	z = (z != 0) ? z / position.z : z;
	dx = (dx != 0) ? dx / position.dx : dx;
	dy = (dy != 0) ? dy / position.dy : dy;
}