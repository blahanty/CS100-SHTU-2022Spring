#ifndef METEORGOODIE_H__
#define METEORGOODIE_H__

#include "Goodie.h"

class MeteorGoodie : public Goodie {
public:
	MeteorGoodie(int x, int y, GameWorld* g);
	void Update() override;
	void Damage(int hp) override;
};

#endif //METEORGOODIE_H__
