#include "Bullet.h"

Bullet::Bullet(int imageID, int x, int y, int direction, double size, int p, GameWorld* g) :
	GameObject(imageID, x, y, direction, 1, size, g), power(p) {}

int Bullet::GetPower() const { return power; }
