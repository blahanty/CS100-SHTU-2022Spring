#ifndef STAR_H__
#define STAR_H__

#include "Decoration.h"

class Star : public Decoration {
public:
	Star(int x, int y, double size);
	void Update() override;
};

#endif //STAR_H__
