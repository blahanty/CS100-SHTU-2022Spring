#ifndef METEOR_H__
#define METEOR_H__

#include "Bullet.h"

class Meteor : public Bullet {
public:
	Meteor(int x, int y, GameWorld* g);
	void Update() override;
};

#endif //METEOR_H__
