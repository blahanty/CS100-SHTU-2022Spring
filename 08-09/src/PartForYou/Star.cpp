#include "Star.h"

Star::Star(int x, int y, double size) : Decoration(IMGID_STAR, x, y, 4, size) {}

void Star::Update() {
	if (GetY() < 0) {
		Destroy();
		return;
	}
	MoveTo(GetX(), GetY() - 1);
}
