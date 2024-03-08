#ifndef DECORATION_H__
#define DECORATION_H__

#include "GameWorld.h"
#include "GameObjects.h"

class Decoration :public GameObject {
public:
	Decoration(int imageID, int x, int y, int layer, double size);
};

#endif //DECORATION_H__
