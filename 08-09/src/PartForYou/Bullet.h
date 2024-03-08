#ifndef BULLET_H__
#define BULLET_H__

#include "GameWorld.h"
#include "GameObjects.h"

class Bullet : public GameObject {
public:
	Bullet(int imageID, int x, int y, int direction, double size, int p, GameWorld* g);
	int GetPower() const override;

private:
	int power;
};

#endif //BULLET_H__
