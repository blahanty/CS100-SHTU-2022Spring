#ifndef REDBULLET_H__
#define REDBULLET_H__

#include "Bullet.h"

class RedBullet : public Bullet {
public:
	RedBullet(int x, int y, int direction, int p, GameWorld* g);
	void Update() override;
};

#endif //REDBULLET_H__
