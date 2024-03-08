#include "Meteor.h"

Meteor::Meteor(int x, int y, GameWorld* g) :
	Bullet(IMGID_METEOR, x, y, 0, 2.0, 1919810, g) {}

void Meteor::Update() {
	if (IsDead())
		return;
	if (GetY() >= WINDOW_HEIGHT) {
		Destroy();
		return;
	}
	if (GetWorld()->JudgeHit(this))
		return;
	MoveTo(GetX(), GetY() + 2);
	SetDirection(GetDirection() + 5);
	if (GetWorld()->JudgeHit(this))
		return;
}
