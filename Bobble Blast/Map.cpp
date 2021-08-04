#include "Map.h"
#include "TextureManager.h"
#include "UsefullFunctions.h"
#include "Input.h"
//desf
///dvgrgvdgbvdtgbv
Map::Map(bool TwoPlayers)
{
	//Size of the tile sheet
	srcRect.w = 16;
	srcRect.h = 16;

	//Size of the tile
	destRect.w = 32;
	destRect.h = 32;

	//is it multiplayer?
	if (TwoPlayers)
		howManyPlayers = 2;
	else
		howManyPlayers = 1;

	//Sets background image
	background = new Background(texturesID::BACKGROUND, Vector2D(0, SCREENHEIGHT), true);
};

Map::~Map()
{
	Clean();
}

void Map::LoadMap(std::string filePath)
{
	//Loads map from file
	UsefullFunctions::LoadMapFromFile(filePath, gridMap);

	//width and height of the vector map
	SetWidth();		SetHeight();

	//Cannon start position
	SetPlayersPos();
}

void Map::LoadColliders(std::string filePath)
{
	UsefullFunctions::LoadMapFromFile(filePath, gridColliders);
	
	AddColliders(); //Add colliders from the loaded map
}

void Map::AddColliders()
{
	int startX1 = 0; //Spawner p1
	int startX2 = 0; //Spawner p2

	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++)
		{
			destRect.x = column * destRect.w;
			destRect.y = row * destRect.h;
			int length;
			switch (gridColliders[row][column])
			{
			case 'V': walls[Walls::P1_WALL].push_back(BoxCollider2D());
				length = UsefullFunctions::CountCharactersinAColumn(gridColliders, row, column);
				walls[Walls::P1_WALL].back().SetBox(destRect.x, destRect.y, destRect.w, destRect.h * length);
				break;
			case 'v': walls[Walls::P2_WALL].push_back(BoxCollider2D());
				length = UsefullFunctions::CountCharactersinAColumn(gridColliders, row, column);
				walls[Walls::P2_WALL].back().SetBox(destRect.x, destRect.y, destRect.w, destRect.h * length);
				break;
			case 'G': walls[Walls::P1_GAMEOVER].push_back(BoxCollider2D());
				length = UsefullFunctions::CountCharactersinARow(gridColliders, row, column) + 1;
				walls[Walls::P1_GAMEOVER].back().SetBox(destRect.x, destRect.y, destRect.w * length, destRect.h);
				//Spawner
				startX1 = destRect.x + (destRect.w * (length / 2));
				break;
			case 'g': walls[Walls::P2_GAMEOVER].push_back(BoxCollider2D());
				length = UsefullFunctions::CountCharactersinARow(gridColliders, row, column) + 1;
				walls[Walls::P2_GAMEOVER].back().SetBox(destRect.x, destRect.y, destRect.w * length, destRect.h);
				//Spawner
				startX2 = destRect.x + (destRect.w * (length / 2));
				break;
			default:
				break;
			}
		}

	//instantiate spawner
	for (int i = 0; i < howManyPlayers; i++)
		Spawner.push_back(new BobbleSpawner((i==0) ? startX1 : startX2));
}

void Map::LoadUI(std::string filePath)
{
	UsefullFunctions::LoadMapFromFile(filePath, gridUI);

	AddUI();  //Add UI from the loaded map
}

void Map::AddUI()
{
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++)
		{
			destRect.x = column * destRect.w;
			destRect.y = row * destRect.h;
			int length;
			switch (gridUI[row][column])
			{
			case 'S': UI.push_back(new UIText(texturesID::P1_SCORE, Fonts::BOBBLE, " "));
				UI.back()->ChangeColor(0, 55, 205, 255);
				UI.back()->SetPos(destRect.x, destRect.y);
				UI.back()->SetWidthAndHeightByText(); 
				break;
			case 's': UI.push_back(new UIText(texturesID::P2_SCORE, Fonts::BOBBLE, " "));
				UI.back()->ChangeColor(243, 38, 15, 255);
				UI.back()->SetPos(destRect.x, destRect.y);
				UI.back()->SetWidthAndHeightByText();
				break;
			default:
				break;
			}
		}
}

void Map::Update(float dt)
{
	//Spawners update
	for (auto it : Spawner)
		it->Update(dt);

	//Player 1 Spawner collisions
	for (BoxCollider2D box : GetWallByKey(Walls::P1_WALL))
		Spawner[0]->CollisionsWall(box.GetBox());
	for (BoxCollider2D box : GetWallByKey(Walls::P1_GAMEOVER))
		Spawner[0]->CollisionsWall(box.GetBox(), true);

	//Player 2 Spawner collisions
	if (howManyPlayers == 2)
	{
		for (BoxCollider2D box : GetWallByKey(Walls::P2_WALL))
			Spawner[1]->CollisionsWall(box.GetBox());
		for (BoxCollider2D box : GetWallByKey(Walls::P2_GAMEOVER))
			Spawner[1]->CollisionsWall(box.GetBox(), true);
	}

	//Background
	background->Update(dt);
	
	//UI
	for (int i = 0; i < UI.size(); i++)
	{
		//Create text
		std::stringstream score;
		score << "Score:\n" << Spawner[i]->GetStats()->GetScore() << "\nLife:\n" << Spawner[i]->GetStats()->GetLives();
		std::string Score = score.str();
		
		UI[i]->SetText(Score);
		UI[i]->SetWidthAndHeightByText();
		UI[i]->Update(100);
	}
}

void Map::Draw()
{
	//Background
	background->Draw();
	
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++)
		{
			destRect.x = column * destRect.w;
			destRect.y = row * destRect.h;

			switch (gridMap[row][column])
			{
			case '4':
				srcRect.x = srcRect.w * 3;
				srcRect.y = srcRect.h * 2;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			case 'a':
				srcRect.x = srcRect.w * 3;
				srcRect.y = srcRect.h * 2;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			case '5':
				srcRect.x = srcRect.w * 5;
				srcRect.y = srcRect.h * 2;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			case '6':
				srcRect.x = srcRect.w * 2;
				srcRect.y = srcRect.h * 3;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			case 'P':
				srcRect.x = srcRect.w * 2;
				srcRect.y = srcRect.h * 3;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			case 'p':
				srcRect.x = srcRect.w * 2;
				srcRect.y = srcRect.h * 3;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			case '7':
				srcRect.x = srcRect.w * 3;
				srcRect.y = srcRect.h * 3;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			case '8':
				srcRect.x = srcRect.w * 4;
				srcRect.y = srcRect.h * 3;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			case '9':
				srcRect.x = srcRect.w * 5;
				srcRect.y = srcRect.h * 3;
				TextureManager::GetInstance()->DrawTile(texturesID::MAP1, srcRect, destRect, row, column);
				break;
			default:
				break;
			}
		}

	//Draw box colliders
#if _DEBUG
	for (const auto& pair : walls)
		for (BoxCollider2D d : pair.second) 
			d.DrawBox(255,255,255,255);
#endif

	//UI
	for (int i = 0; i < UI.size(); i++)
		UI[i]->Draw(One);

	//Spawner(s)
	for (auto it : Spawner)
		it->Draw();
}

void Map::Clean()
{
	if (background != nullptr)
	{
		delete background;
		background = nullptr;
	}
	if (Spawner.size() > 0)
	{
		for (int i = 0; i < Spawner.size(); i++)
		{
			delete Spawner[i];
			Spawner[i] = nullptr;
		}
		Spawner.clear();
	}
	if (UI.size() > 0)
	{
		for (int i = 0; i < UI.size(); i++)
		{
			delete UI[i];
			UI[i] = nullptr;
		}
		UI.clear();
	}
}

void Map::SetPlayersPos()
{
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++)
		{
			destRect.x = column * destRect.w;
			destRect.y = row * destRect.h;
			
			switch (gridMap[row][column])
			{
			case 'P': //Player 1
				P1Pos.x = destRect.x - (destRect.w / 4);
				P1Pos.y = destRect.y - (destRect.h / 2);
				break;
			case 'p': //Player 2
				P2Pos.x = destRect.x - (destRect.w / 4);
				P2Pos.y = destRect.y - (destRect.h / 2);
				break;
			default:
				break;
			}
		}
}

void Map::SetWidth()
{
	width = gridMap[0].length();
}

void Map::SetHeight()
{
	height = gridMap.size();
}
