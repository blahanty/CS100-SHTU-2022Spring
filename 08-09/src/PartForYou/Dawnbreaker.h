#ifndef DAWNBREAKER_H__
#define DAWNBREAKER_H__

#include "GameWorld.h"
#include "GameObjects.h"
#include "BlueBullet.h"
#include "Meteor.h"

class Dawnbreaker : public GameObject {
public:
	Dawnbreaker(GameWorld* g);
	void Update() override;
	void Damage(int hp) override;
	int GetHP() const;
	int GetMeteors() const;
	void SetHP(int hp);
	void SetMeteors(int m);
	void Upgrade();

private:
	int HP, energy, meteors, grade;
};

#endif //DAWNBREAKER_H__
