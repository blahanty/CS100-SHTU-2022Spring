#include "Alphatron.h"

Alphatron::Alphatron(int x, int y, int hp, int p, int v, GameWorld* g) :
	Plane(IMGID_ALPHATRON, x, y, hp, p, v, 25, g) {}

void Alphatron::Update() {
	if (IsDead())
		return;
	if (GetY() < 0) {
		Destroy();
		return;
	}
	if (GetWorld()->JudgeHit(this))
		return;
	if (abs(GetX() - GetWorld()->GetDawnbreaker()->GetX()) <= 10)
		if (GetEnergy() >= 25) {
			int random = randInt(114511, 114514);
			if (random == 114514) {
				GetWorld()->AddObject(new RedBullet(GetX(), GetY() - 50, 180, GetPower(), GetWorld()));
				SetEnergy(GetEnergy() - 25);
			}
		}
	if (GetEnergy() < 25)
		SetEnergy(GetEnergy() + 1);
	Move();
	if (GetWorld()->JudgeHit(this))
		return;
}

void Alphatron::Wreck() {
	Destroy();
	GetWorld()->AddObject(new Explosion(GetX(), GetY()));
	GetWorld()->IncreaseScore(50);
	GetWorld()->SetDestroyed(GetWorld()->GetDestroyed() + 1);
}
