#ifndef PLANE_H__
#define PLANE_H__

#include "GameWorld.h"
#include "GameObjects.h"
#include "RedBullet.h"
#include "Explosion.h"

class Plane : public GameObject {
public:
	Plane(int imageID, int x, int y, int hp, int p, int v, int e, GameWorld* g);
	virtual void Wreck() = 0;
	int GetEnergy() const;
	int GetPower() const;
	void SetEnergy(int e);
	void SetSpeed(int v);
	void SetStrategy(int s);
	void SetTime(int t);
	void Damage(int hp) override;

protected:
	void Move();

private:
	int HP, power, speed, energy, strategy, time;
};

#endif //PLANE_H__
