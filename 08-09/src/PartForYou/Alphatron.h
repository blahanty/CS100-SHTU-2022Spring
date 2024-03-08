#ifndef ALPHATRON_H__
#define ALPHATRON_H__

#include "Plane.h"

class Alphatron : public Plane {
public:
	Alphatron(int x, int y, int hp, int p, int v, GameWorld* g);
	void Update() override;
	void Wreck() override;
};

#endif //ALPHATRON_H__
