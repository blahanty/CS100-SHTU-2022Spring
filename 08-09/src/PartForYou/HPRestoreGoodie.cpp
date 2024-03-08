#include "HPRestoreGoodie.h"

HPRestoreGoodie::HPRestoreGoodie(int x, int y, GameWorld* g) :
	Goodie(IMGID_HP_RESTORE_GOODIE, x, y, g) {}

void HPRestoreGoodie::Update() {
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

void HPRestoreGoodie::Damage(int hp) {
	GetWorld()->GetDawnbreaker()->SetHP(GetWorld()->GetDawnbreaker()->GetHP());
	GetWorld()->IncreaseScore(20);
	Destroy();
}
