#ifndef POWERUPGOODIE_H__
#define POWERUPGOODIE_H__

#include "Goodie.h"

class PowerUpGoodie : public Goodie {
public:
	PowerUpGoodie(int x, int y, GameWorld* g);
	void Update() override;
	void Damage(int hp) override;
};

#endif //POWERUPGOODIE_H__
