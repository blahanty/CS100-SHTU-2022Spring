#ifndef HPRESTOREGOODIE_H__
#define HPRESTOREGOODIE_H__

#include "Goodie.h"

class HPRestoreGoodie : public Goodie {
public:
	HPRestoreGoodie(int x, int y, GameWorld* g);
	void Update() override;
	void Damage(int hp) override;
};

#endif //HPRESTOREGOODIE_H__
