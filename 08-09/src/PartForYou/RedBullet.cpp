#include "RedBullet.h"

RedBullet::RedBullet(int x, int y, int direction, int power, GameWorld* g) :
	Bullet(IMGID_RED_BULLET, x, y, direction, 0.5, power, g) {}

void RedBullet::Update() {
	if (IsDead())
		return;
	if (GetY() < 0) {
		Destroy();
		return;
	}
	if (GetWorld()->JudgeHit(this)) {
		Destroy();
		return;
	}
	switch (GetDirection())
	{
	default:
		MoveTo(GetX(), GetY() - 6);
		break;
	case 162:
		MoveTo(GetX() + 2, GetY() - 6);
		break;
	case 198:
		MoveTo(GetX() - 2, GetY() - 6);
		break;
	}
	if (GetWorld()->JudgeHit(this))
		Destroy();
}
