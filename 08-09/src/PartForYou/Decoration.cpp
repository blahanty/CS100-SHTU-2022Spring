#include "Decoration.h"

Decoration::Decoration(int imageID, int x, int y, int layer, double size) :
    GameObject(imageID, x, y, 0, layer, size, nullptr) {}
