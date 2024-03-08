#include "GameWorld.h"
#include "GameObjects.h"

GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* g) :
	ObjectBase(imageID, x, y, direction, layer, size), gameWorld(g), alive(true) {
	switch (imageID)
	{
	case IMGID_DAWNBREAKER:
		type = 'd';
		break;
	case IMGID_BLUE_BULLET:
		type = 'b';
		break;
	case IMGID_RED_BULLET:
		type = 'r';
		break;
	case IMGID_METEOR:
		type = 'm';
		break;
	default:
		if (imageID >= 2 && imageID <= 4) //Alphatron, Sigmatron or Omegatron
			type = 'p';
		else if (imageID >= 9) //Goodie
			type = 'g';
		else //Star or Explosion
			type = 'n';
		break;
	}
}

bool GameObject::IsDead() const { return !alive; }

void GameObject::Destroy() { alive = false; }

void GameObject::Damage(int hp) {};

char GameObject::GetType() const { return type; }

int GameObject::GetPower() const { return 1919810; }

int GameObject::GetHP() const { return 114514; }

int GameObject::GetMeteors() const { return 114514; }

void GameObject::SetHP(int hp) {}

void GameObject::SetMeteors(int m) {}

void GameObject::Upgrade() {}

GameWorld* GameObject::GetWorld() const { return gameWorld; }
