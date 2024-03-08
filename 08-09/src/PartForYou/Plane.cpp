#include "Plane.h"

Plane::Plane(int imageID, int x, int y, int hp, int p, int v, int e, GameWorld* g) :
	GameObject(imageID, x, y, 180, 0, 1.0, g), HP(hp), power(p), speed(v), energy(e), strategy(0), time(0) {}

int Plane::GetEnergy() const { return energy; }

int Plane::GetPower() const { return power; }

void Plane::SetEnergy(int e) { energy = e; }

void Plane::SetSpeed(int v) { speed = v; }

void Plane::SetStrategy(int s) { strategy = s; }

void Plane::SetTime(int t) { time = t; }

void Plane::Damage(int hp) {
	HP -= hp;
	if (HP <= 0)
		Wreck();
}

void Plane::Move() {
	if (GetX() < 0 || GetX() >= WINDOW_WIDTH || !time) {
		if (GetX() < 0)
			strategy = 3;
		else if (GetX() >= WINDOW_WIDTH)
			strategy = 1;
		else if (!time)
			strategy = randInt(1, 3);
		time = randInt(10, 50);
	}
	switch (strategy)
	{
	default:
		break;
	case 1:
		MoveTo(GetX() - speed, GetY() - speed);
		break;
	case 2:
		MoveTo(GetX(), GetY() - speed);
		break;
	case 3:
		MoveTo(GetX() + speed, GetY() - speed);
		break;
	}
	--time;
}
