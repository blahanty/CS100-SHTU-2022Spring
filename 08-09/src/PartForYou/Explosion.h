#ifndef EXPLOSION_H__
#define EXPLOSION_H__

#include "Decoration.h"

class Explosion : public Decoration {
public:
	Explosion(int x, int y);
	void Update() override;

private:
	int	tick;
};

#endif //EXPLOSION_H__
