#pragma once
#include "../../include/Math/Vector2.h"
#include "Background.h"
#include "BobbleSpawner.h"
#include <map>
#include <string>
#include <vector>


//Colliders
enum class Walls
{
	P1_WALL,
	P1_GAMEOVER,
	P2_WALL,
	P2_GAMEOVER,
	ALL_COLLIDERS
};


class Background;
class BobbleSpawner;
class BoxCollider2D;


class Map
{
private:
	Background* background;

	std::vector<BobbleSpawner*> Spawner;

	std::vector<UIText*> UI;

	std::vector<std::string> gridMap;

	std::vector<std::string> gridColliders;
	
	std::vector<std::string> gridUI;

	std::map<Walls, std::vector<BoxCollider2D>> walls;
	
	SDL_Rect srcRect;
	
	SDL_Rect destRect;
	
	int width{ 0 }; 
	
	int height{ 0 };

	Vector2 P1Pos;

	Vector2 P2Pos;

	int howManyPlayers;


	void AddColliders();
	
	void AddUI();


public:
	Map(bool twoPlayers = false);

	~Map();

	
	void LoadMap(std::string filePath);
	
	void LoadColliders(std::string filePath);
	
	void LoadUI(std::string filePath);

	void Update(float dt);
	
	void Draw();

	void Clean();

	void SetPlayersPos();
	
	void SetWidth();
	
	void SetHeight();

	Vector2 GetP1Pos() const;
	
	Vector2 GetP2Pos() const;
	
	const std::map<Walls, std::vector<BoxCollider2D>>& GetWalls();
	
	const std::vector<BoxCollider2D>& GetWallByKey(Walls key);
	
	const std::vector<BobbleSpawner*>& GetSpawner();
};