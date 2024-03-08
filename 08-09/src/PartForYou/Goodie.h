#ifndef GOODIE_H__
#define GOODIE_H__

#include "GameWorld.h"
#include "GameObjects.h"

class Goodie : public GameObject {
public:
	Goodie(int imageID, int x, int y, GameWorld* g);
};

#endif //GOODIE_H__
