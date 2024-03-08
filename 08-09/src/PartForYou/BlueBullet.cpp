#include "BlueBullet.h"

BlueBullet::BlueBullet(int x, int y, double size, int power, GameWorld* g) :
	Bullet(IMGID_BLUE_BULLET, x, y, 0, size, power, g) {}

void BlueBullet::Update() {
	if (IsDead())
		return;
	if (GetY() >= WINDOW_HEIGHT) {
		Destroy();
		return;
	}
	if (GetWorld()->JudgeHit(this)) {
		Destroy();
		return;
	}
	MoveTo(GetX(), GetY() + 6);
	if (GetWorld()->JudgeHit(this))
		Destroy();
}
