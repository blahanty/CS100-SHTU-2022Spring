#ifndef BLUEBULLET_H__
#define BLUEBULLET_H__

#include "Bullet.h"

class BlueBullet : public Bullet {
public:
	BlueBullet(int x, int y, double size, int p, GameWorld* g);
	void Update() override;
};

#endif //BLUEBULLET_H__
