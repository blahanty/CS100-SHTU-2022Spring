#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>

#include "WorldBase.h"

class GameObject;

class GameWorld : public WorldBase {
public:
	GameWorld();
	~GameWorld() override;
	void Init() override;
	LevelStatus Update() override;
	void CleanUp() override;
	bool IsGameOver() const override;
	int GetDestroyed() const;
	void SetDestroyed(int d);
	void AddObject(GameObject* gameObject);
	bool IsHit(GameObject* a, GameObject* b) const;
	bool JudgeHit(GameObject* gameObject);
	GameObject* GetDawnbreaker() const;

private:
	std::list<GameObject*> objects;
	int lives, level, destroyed, required, maxOnScreen, p1, p2, p3, Score;
};

#endif // !GAMEWORLD_H__
