#include "Explosion.h"

Explosion::Explosion(int x, int y) :
	Decoration(IMGID_EXPLOSION, x, y, 3, 4.5), tick(0) {}

void Explosion::Update() {
	SetSize(GetSize() - 0.2);
	if (++tick == 20)
		Destroy();
}
