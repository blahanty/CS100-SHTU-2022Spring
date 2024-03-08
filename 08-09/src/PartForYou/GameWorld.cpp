#include "GameWorld.h"
#include "GameObjects.h"
#include "Dawnbreaker.h"
#include "Star.h"
#include "Alphatron.h"
#include "Sigmatron.h"
#include "Omegatron.h"

GameWorld::GameWorld() : lives(3), level(0), destroyed(0), required(0), maxOnScreen(0), p1(0), p2(0), p3(0), Score(0) {};

GameWorld::~GameWorld() {}

void GameWorld::Init() {
	level = GetLevel();
	destroyed = 0;
	required = 3 * level;
	maxOnScreen = (int)((5 + level) / 2);
	p1 = 6;
	p2 = 2 * std::max((level - 1), 0);
	p3 = 3 * std::max((level - 2), 0);
	objects.push_back(new Dawnbreaker(this));
	for (int i = 0; i < 30; ++i)
		objects.push_back(new Star(randInt(0, WINDOW_WIDTH - 1),
			randInt(0, WINDOW_HEIGHT - 1),
			(double)randInt(10, 40) / 100));
}

LevelStatus GameWorld::Update() {
	if (randInt(114500, 114529) == 114514)
		objects.push_back(new Star(randInt(0, WINDOW_WIDTH - 1),
			WINDOW_HEIGHT - 1,
			(double)randInt(10, 40) / 100));
	int toDestroy = required - destroyed;
	int allowed = std::min(toDestroy, maxOnScreen);
	int onScreen = 0;
	for (auto& object : objects)
		if (object->GetType() == 'p')
			++onScreen;
	if (onScreen < allowed) {
		if (randInt(1, 100) <= allowed - onScreen) {
			int random = randInt(1, p1 + p2 + p3);
			if (random <= p1)
				AddObject(new Alphatron(randInt(0, WINDOW_WIDTH - 1),
					WINDOW_HEIGHT - 1, 20 + 2 * level, 4 + level, 2 + floor(level / 5), this));
			else if (random <= p1 + p2)
				AddObject(new Sigmatron(randInt(0, WINDOW_WIDTH - 1),
					WINDOW_HEIGHT - 1, 25 + 5 * level, 2 + floor(level / 5), this));
			else
				AddObject(new Omegatron(randInt(0, WINDOW_WIDTH - 1),
					WINDOW_HEIGHT - 1, 20 + level, 2 + 2 * level, 3 + floor(level / 4), this));
		}
	}
	for (auto& object : objects)
		object->Update();
	if (GetDawnbreaker()->IsDead()) {
		--lives;
		return LevelStatus::DAWNBREAKER_DESTROYED;
	}
	if (destroyed >= required)
		return LevelStatus::LEVEL_CLEARED;
	for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end();)
		if ((*iter)->IsDead()) {
			delete (*iter);
			iter = objects.erase(iter);
		}
		else
			++iter;
	SetStatusBarMessage("HP: " + std::to_string(GetDawnbreaker()->GetHP()) +
		"/100   Meteors: " + std::to_string(GetDawnbreaker()->GetMeteors()) +
		"   Lives: " + std::to_string(lives) +
		"   Level: " + std::to_string(level) +
		"   Enemies: " + std::to_string(destroyed) + "/" + std::to_string(required) +
		"   Score: " + std::to_string(GetScore()));
	return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
	for (auto& object : objects)
		delete object;
	objects.clear();
}

bool GameWorld::IsGameOver() const {
	return !lives;
}

int GameWorld::GetDestroyed() const { return destroyed; }

void GameWorld::SetDestroyed(int d) { destroyed = d; }

void GameWorld::AddObject(GameObject* gameObject) { objects.push_back(gameObject); }

bool GameWorld::IsHit(GameObject* a, GameObject* b) const {
	double d = sqrt(pow(a->GetX() - b->GetX(), 2) + pow(a->GetY() - b->GetY(), 2));
	return d < 30.0 * (a->GetSize() + b->GetSize());
}

bool GameWorld::JudgeHit(GameObject* gameObject) {
	for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
		if (*iter != gameObject && !(*iter)->IsDead() && IsHit(gameObject, *iter))
			switch (gameObject->GetType())
			{
			default:
				break;
			case 'b':
				if ((*iter)->GetType() == 'p') {
					(*iter)->Damage(gameObject->GetPower());
					return true;
				}
				break;
			case 'm':
				if ((*iter)->GetType() == 'p') {
					(*iter)->Damage(1919810);
					return true;
				}
				break;
			case 'r':
				if ((*iter)->GetType() == 'd') {
					GetDawnbreaker()->Damage(gameObject->GetPower());
					return true;
				}
				else
					return false;
				break;
			case 'p':
				if ((*iter)->GetType() == 'd') {
					GetDawnbreaker()->Damage(20);
					gameObject->Damage(1919810);
					return true;
				}
				else if ((*iter)->GetType() == 'b') {
					gameObject->Damage((*iter)->GetPower());
					(*iter)->Destroy();
					return true;
				}
				break;
			case 'g':
				if ((*iter)->GetType() == 'd') {
					gameObject->Damage(1919810);
					return true;
				}
			}
	return false;
}

GameObject* GameWorld::GetDawnbreaker() const {
	return *objects.begin();
}