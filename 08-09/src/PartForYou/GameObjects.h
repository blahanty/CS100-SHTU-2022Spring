#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"

class GameWorld;

class GameObject : public ObjectBase {
public:
	GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* g);
	bool IsDead() const;
	void Destroy();
	virtual void Damage(int hp);
	char GetType() const;
	virtual int GetPower() const;
	virtual int GetHP() const;
	virtual int GetMeteors() const;
	virtual void SetHP(int hp);
	virtual void SetMeteors(int m);
	virtual void Upgrade();

protected:
	GameWorld* GetWorld() const;

private:
	char type;
	bool alive;
	GameWorld* gameWorld;
};

#endif // GAMEOBJECTS_H__