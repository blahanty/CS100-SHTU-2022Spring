#include "MeteorGoodie.h"

MeteorGoodie::MeteorGoodie(int x, int y, GameWorld* g) :
	Goodie(IMGID_METEOR_GOODIE, x, y, g) {}

void MeteorGoodie::Update() {
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

void MeteorGoodie::Damage(int hp) {
	GetWorld()->GetDawnbreaker()->SetMeteors(GetWorld()->GetDawnbreaker()->GetMeteors() + 1);
	GetWorld()->IncreaseScore(20);
	Destroy();
}