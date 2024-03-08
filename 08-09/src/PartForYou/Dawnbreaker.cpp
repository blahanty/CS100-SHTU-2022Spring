#include "Dawnbreaker.h"

Dawnbreaker::Dawnbreaker(GameWorld* g) :
	GameObject(IMGID_DAWNBREAKER, 300, 100, 0, 0, 1.0, g), HP(100), energy(10), meteors(0), grade(0) {}

void Dawnbreaker::Update() {
	if (IsDead())
		return;
	if (GetWorld()->GetKey(KeyCode::UP))
		if (GetY() + 4 < WINDOW_HEIGHT)
			MoveTo(GetX(), GetY() + 4);
	if (GetWorld()->GetKey(KeyCode::DOWN))
		if (GetY() - 4 > 50)
			MoveTo(GetX(), GetY() - 4);
	if (GetWorld()->GetKey(KeyCode::LEFT))
		if (GetX() - 4 > 0)
			MoveTo(GetX() - 4, GetY());
	if (GetWorld()->GetKey(KeyCode::RIGHT))
		if (GetX() + 4 < WINDOW_WIDTH)
			MoveTo(GetX() + 4, GetY());
	if (GetWorld()->GetKey(KeyCode::FIRE1))
		if (energy >= 10) {
			GetWorld()->AddObject(new BlueBullet(GetX(), GetY() + 50, 0.5 + 0.1 * grade, 5 + 3 * grade, GetWorld()));
			energy -= 10;
		}
	if (GetWorld()->GetKeyDown(KeyCode::FIRE2))
		if (meteors) {
			GetWorld()->AddObject(new Meteor(GetX(), GetY() + 100, GetWorld()));
			--meteors;
		}
	if (energy < 10)
		++energy;
}

void Dawnbreaker::Damage(int hp) {
	HP -= hp;
	if (HP <= 0)
		Destroy();
}

int Dawnbreaker::GetHP() const { return HP; }

int Dawnbreaker::GetMeteors() const { return meteors; }

void Dawnbreaker::SetHP(int hp) {
	HP += hp;
	if (HP > 100)
		HP = 100;
}

void Dawnbreaker::SetMeteors(int m) { meteors = m; }

void Dawnbreaker::Upgrade() { ++grade; }
