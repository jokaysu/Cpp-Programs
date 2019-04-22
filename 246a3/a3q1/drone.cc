#include "drone.h"

//private part of drone.cc
//****************
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

int myabs(int n) {
	if (n < 0) return -n;
		else return n;
}
//****************

Position::Position(int ew, int ns): ew(ew), ns(ns) { }

Drone::Drone() {
	x = 0;
	y = 0;
	for (int i = 0; i < 122; ++i) 
		for (int j = 0 ; j < 122; ++j) 
			v[i][j] = false;
	d = 0;
	face = NORTH;
}

Drone::~Drone() { }

void Drone::forward() {
	v[x + 60][y + 60] = true;
	switch (face) {
		case NORTH: 
			y++;
			break;
		case SOUTH: 
			y--;
			break;
		case EAST: 
			x++;
			break;
		case WEST:
			x--;
			break;
	}
	d++;
}

void Drone::backward() {
	v[x + 60][y + 60] = true;
	switch (face) {
		case NORTH: 
			y--;
			break;
		case SOUTH: 
			y++;
			break;
		case EAST: 
			x--;
			break;
		case WEST:
			x++;
			break;
	}
	d++;
}

void Drone::left() {
	switch (face) {
		case NORTH: 
			face = WEST;
			break;
		case SOUTH: 
			face = EAST;
			break;
		case EAST: 
			face = NORTH;
			break;
		case WEST:
			face = SOUTH;
			break;
	}
}

void Drone::right() {
	switch (face) {
		case NORTH: 
			face = EAST;
			break;
		case SOUTH: 
			face = WEST;
			break;
		case EAST: 
			face = SOUTH;
			break;
		case WEST:
			face = NORTH;
			break;
	}
}

Position Drone::current() const {
	return Position(x, y);
}

int Drone::totalDistance() const {
	return d;
}

int Drone::manhattanDistance() const {
	return myabs(x) + myabs(y);
}

bool Drone::repeated() const {
	return v[x + 60][y + 60];
}
