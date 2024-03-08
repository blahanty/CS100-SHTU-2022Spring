#include "Omegatron.h"

Omegatron::Omegatron(int x, int y, int hp, int p, int v, GameWorld* g) :
	Plane(IMGID_OMEGATRON, x, y, hp, p, v, 50, g) {}

void Omegatron::Update() {
	if (IsDead())
		return;
	if (GetY() < 0) {
		Destroy();
		return;
	}
	if (GetWorld()->JudgeHit(this))
		return;
	if (GetEnergy() >= 50) {
		GetWorld()->AddObject(new RedBullet(GetX(), GetY() - 50, 162, GetPower(), GetWorld()));
		GetWorld()->AddObject(new RedBullet(GetX(), GetY() - 50, 198, GetPower(), GetWorld()));
		SetEnergy(GetEnergy() - 50);
	}
	if (GetEnergy() < 50)
		SetEnergy(GetEnergy() + 1);
	Move();
	if (GetWorld()->JudgeHit(this))
		return;
}

void Omegatron::Wreck() {
	Destroy();
	GetWorld()->AddObject(new Explosion(GetX(), GetY()));
	GetWorld()->IncreaseScore(200);
	GetWorld()->SetDestroyed(GetWorld()->GetDestroyed() + 1);
	if (randInt(114511, 114515) >= 114514)
		if (randInt(114511, 114515) == 114514)
			GetWorld()->AddObject(new MeteorGoodie(GetX(), GetY(), GetWorld()));
		else
			GetWorld()->AddObject(new PowerUpGoodie(GetX(), GetY(), GetWorld()));

}