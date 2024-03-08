#include "PowerUpGoodie.h"

PowerUpGoodie::PowerUpGoodie(int x, int y, GameWorld* g) :
	Goodie(IMGID_POWERUP_GOODIE, x, y, g) {}

void PowerUpGoodie::Update() {
	if (IsDead())
		return;
	if (GetY() < 0) {
		Destroy();
		return;
	}
	if (GetWorld()->JudgeHit(this))
		return;
	MoveTo(GetX(), GetY() - 2);
	if (GetWorld()->JudgeHit(this))
		return;
}

void PowerUpGoodie::Damage(int hp) {
	GetWorld()->GetDawnbreaker()->Upgrade();
	GetWorld()->IncreaseScore(20);
	Destroy();
}
