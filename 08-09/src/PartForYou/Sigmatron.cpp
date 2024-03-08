#include "Sigmatron.h"

Sigmatron::Sigmatron(int x, int y, int hp, int v, GameWorld* g) :
	Plane(IMGID_SIGMATRON, x, y, hp, 0, v, 0, g) {}

void Sigmatron::Update() {
	if (IsDead())
		return;
	if (GetY() < 0) {
		Destroy();
		return;
	}
	if (GetWorld()->JudgeHit(this))
		return;
	if (abs(GetX() - GetWorld()->GetDawnbreaker()->GetX()) <= 10) {
		SetSpeed(10);
		SetStrategy(2);
		SetTime(WINDOW_HEIGHT + 114514);
	}
	Move();
	if (GetWorld()->JudgeHit(this))
		return;
}

void Sigmatron::Wreck() {
	Destroy();
	GetWorld()->AddObject(new Explosion(GetX(), GetY()));
	GetWorld()->IncreaseScore(100);
	GetWorld()->SetDestroyed(GetWorld()->GetDestroyed() + 1);
	if (randInt(114511, 114515) == 114514)
		GetWorld()->AddObject(new HPRestoreGoodie(GetX(), GetY(), GetWorld()));
}
