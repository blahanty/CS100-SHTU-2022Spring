#ifndef SIGMATRON_H__
#define SIGMATRON_H__

#include "Plane.h"
#include "HPRestoreGoodie.h"

class Sigmatron : public Plane {
public:
	Sigmatron(int x, int y, int hp, int v, GameWorld* g);
	void Update() override;
	void Wreck() override;
};

#endif //SIGMATRON_H__
