#ifndef OMEGATRON_H__
#define OMEGATRON_H__

#include "Plane.h"
#include "MeteorGoodie.h"
#include "PowerUpGoodie.h"

class Omegatron : public Plane {
public:
	Omegatron(int x, int y, int hp, int p, int v, GameWorld* g);
	void Update() override;
	void Wreck() override;
};

#endif //OMEGATRON_H__
