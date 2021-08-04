#pragma once
#include "BoxCollider2D.h"
#include "BobbleSpawner.h"
#include "Background.h"
#include "UIText.h"


//Colliders
enum class Walls
{
	P1_WALL,
	P1_GAMEOVER,
	P2_WALL,
	P2_GAMEOVER,
	ALL_COLLIDERS
};


class Map
{
private:
	Background* background;

	std::vector<BobbleSpawner*> Spawner;

	std::vector<UIText*> UI;

	//Grids
	std::vector<std::string> gridMap;
	std::vector<std::string> gridColliders;
	std::vector<std::string> gridUI;

	std::map<Walls, std::vector<BoxCollider2D>> walls;
	SDL_Rect srcRect{}, destRect{};
	int width{ 0 }, height{ 0 };

	Vector2D P1Pos;
	Vector2D P2Pos;

	int howManyPlayers;


public:
	Map(bool TwoPlayers = false);
	~Map();

	//Loading from file
	void LoadMap(std::string filePath);
	void LoadColliders(std::string filePath);
	void LoadUI(std::string filePath);

	void Update(float dt);
	void Draw();

	void Clean();

private:
	void AddColliders();
	void AddUI();

public:
	//Setters
	void SetPlayersPos();
	void SetWidth();
	void SetHeight();

	//Getters
	Vector2D GetP1Pos() { return P1Pos; }
	Vector2D GetP2Pos() { return P2Pos; }
	inline std::map<Walls, std::vector<BoxCollider2D>> GetWalls() { return walls; }
	inline std::vector<BoxCollider2D> GetWallByKey(Walls key) { return walls[key]; }
	inline std::vector<BobbleSpawner*> GetSpawner() { return Spawner; }
	inline bool IsMultiplayer() { return howManyPlayers == 2; }
};