#include "Application.h"
#include "Renderer.h"
#include "TextureManager.h"
#include "Input.h"
#include "Timer.h"
#include "MessageHandler.h"
#if _DEBUG
#include "MemoryManagement.h"
#endif

Application::Application()
{
	srand(time(NULL));

	Running = true;
	gameover = false;

	//Load textures
	TextureManager::GetInstance()->LoadTextures("Assets/Textures.txt");
	TextureManager::GetInstance()->SetTexture(texturesID::END_GAME_BACKGROUND, EndGameFadeTexture());
	//Load Fonts
	UIManager::GetInstance()->LoadFonts(Fonts::BOBBLE, "Assets/Fonts/BubbleBobble/BubbleBobble.ttf", 40);
	//Audio SFX
	AudioManager::GetInstance()->LoadAudio(0, "Assets/Audio/Bubble Blow.wav", SFX, 20);
	AudioManager::GetInstance()->LoadAudio(1, "Assets/Audio/Spawn.ogg", SFX, 20);
	AudioManager::GetInstance()->LoadAudio(2, "Assets/Audio/Bounce.wav", SFX, 5);
	AudioManager::GetInstance()->LoadAudio(3, "Assets/Audio/bubble-shot.wav", SFX, 10);
	AudioManager::GetInstance()->LoadAudio(4, "Assets/Audio/GameOver.mp3", SFX, 40);
	//Audio Music
	AudioManager::GetInstance()->LoadAudio(0, "Assets/Audio/AIr Room.wav", MUSIC, 15);
	AudioManager::GetInstance()->LoadAudio(1, "Assets/Audio/Blazer Rail 2.wav", MUSIC, 15);

	//Player
	cannon.clear();

	//FPS text
	FPSText = new UIText(texturesID::FPS_COUNTER, Fonts::BOBBLE, " ");
	FPSText->SetPos(0, 0);
	FPSText->ChangeColor(235, 219, 7, 255);
	//GameOver text
	GameOverText = new UIText(texturesID::END_GAME_TEXT, Fonts::BOBBLE, " ");
	GameOverText->SetPos(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	GameOverText->ChangeColor(0, 205, 55, 255);
}

Application::~Application()
{
	Destroy();
}

void Application::Update()
{
	Input::GetInstance()->Update();

	//Check if at least one controller is plugged in
	MessageHandler Message;
	if (Input::GetInstance()->GetControllersNumber() == 0)
	{
		Message.ShowMessageBox(messageType::CONTROLLER_WARNING);
	}

	//-------------------MAIN MENU----------------------
	MenuUpdate();

	//----------INIT MAP, COLLIDERS, GAME MODE-------------------
	AudioManager::GetInstance()->FadeMusicTrack(1, -1, 1000);
	map = new Map(TwoPlayers);

	//Game instructions
	if (Running)
		Message.ShowMessageBox(messageType::INSTRUCTIONS);

	//Load map
	if (!map->IsMultiplayer())
		map->LoadMap("Assets/Map/SinglePlayer/Map.txt");
	else
		map->LoadMap("Assets/Map/Multiplayer/Map.txt");

	//Load player(s) and colliders and UI
	cannon.push_back(new Cannon(map->GetP1Pos(), (int)Players::PLAYER1));
	if (map->IsMultiplayer())
	{
		cannon.push_back(new Cannon(map->GetP2Pos(), (int)Players::PLAYER2));
		map->LoadColliders("Assets/Map/Multiplayer/BoxColliders.txt");
		map->LoadUI("Assets/Map/Multiplayer/UIText.txt");
	}
	else
	{
		map->LoadColliders("Assets/Map/SinglePlayer/BoxColliders.txt");
		map->LoadUI("Assets/Map/SinglePlayer/UIText.txt");
	}

	//---------------GAME UPDATE------------------ 
	while (Running)
	{
		if (Renderer::GetInstance()->GetRenderer())
		{
			ft.StartClock();

			if (!Input::GetInstance()->Update())
				Quit();

			if (!gameover)
			{
				//Updates
				for (auto it : cannon)
					it->Update(FrameTimer::DeltaTime());

				map->Update(FrameTimer::DeltaTime());

				FPSText->SetWidthAndHeightByText();
				FPSText->Update(100);

				//Check if gameover
				for (int i = 0; i < map->GetSpawner().size(); i++)
				{
					if (map->GetSpawner()[i]->GetStats()->GetLives() <= 0)
					{
						map->GetSpawner()[i]->RemoveTimers();

						cannon[i]->SetGameover(true);
					}
				}
				if (TwoPlayers)
				{
					if (cannon.front()->GetGameOver() && cannon.back()->GetGameOver())
					{
						gameover = true;
						AudioManager::GetInstance()->StopMusic();
						AudioManager::GetInstance()->PlaySFX(4, 0, 0);
					}
				}
				else
				{
					if (cannon.front()->GetGameOver())
					{
						gameover = true;
						AudioManager::GetInstance()->StopMusic();
						AudioManager::GetInstance()->PlaySFX(4, 0, 0);
					}
				}


				//Collisions (Player's bobble) with wall and falling bobbles
				int index = 0;
				for (auto it : cannon)
				{
					if (it->GetBobble() != nullptr)
					{
						if (index == 0)
						{
							for (BoxCollider2D i : map->GetWallByKey(Walls::P1_WALL))
								it->GetBobble()->CollisionsWithWall(i.GetBox());
							map->GetSpawner().front()->CollisionsBobble(it->GetBobble());
						}
						else
						{
							for (BoxCollider2D i : map->GetWallByKey(Walls::P2_WALL))
								it->GetBobble()->CollisionsWithWall(i.GetBox());
							map->GetSpawner().back()->CollisionsBobble(it->GetBobble());
						}
						++index;
					}
				}
			}

			//Rendering
			map->Draw();

			for (auto it : cannon)
				it->Draw();

			FPSText->Draw(One);

			//End game
			if (gameover)
			{
				//Create text
				std::stringstream message;
				std::string Mess;

				if (TwoPlayers)
				{
					if (map->GetSpawner().front()->GetStats()->GetScore() > map->GetSpawner().back()->GetStats()->GetScore())
					{
						message << "\t\tThe winner is Player 1!\n\t\t\t\t\t\tScore: " << map->GetSpawner().front()->GetStats()->GetScore() << "\n\n Press B to exit the game...";
						Mess = message.str();
					}
					else if (map->GetSpawner().front()->GetStats()->GetScore() < map->GetSpawner().back()->GetStats()->GetScore())
					{
						message << "\t\tThe winner is Player 2!\n\t\t\t\t\t\tScore: " << map->GetSpawner().back()->GetStats()->GetScore() << "\n\n Press B to exit the game...";
						Mess = message.str();
					}
					else
					{
						message << "\t\t\t\t\t\tIt's a draw!" << "\n\n Press B to exit the game...";
						Mess = message.str();
					}
				}
				else
				{
					message << "\t\t\t\t\t\t\tGameOver\n" << "\t\t\t\tYour Score: " << map->GetSpawner().front()->GetStats()->GetScore() << "\n\n Press B to exit the game...";
					Mess = message.str();
				}

				GameOverText->SetText(Mess);
				GameOverText->SetWidthAndHeightByText();
				GameOverText->Update(440);
				TextureManager::GetInstance()->NormalDraw(texturesID::END_GAME_BACKGROUND);
				GameOverText->Draw(One, true);

				if (Input::GetInstance()->ButtonPressed(Players::PLAYER1, SDL_CONTROLLER_BUTTON_B))
					Quit();
			}

			Renderer::GetInstance()->ClearAndPresent();

			//FPS and delay
			ft.EndClock();
			ft.DelayByFrameTime();
			FPSText->SetText(std::to_string(FrameTimer::Frames()));
		}
	}
}

void Application::MenuUpdate()
{
	AudioManager::GetInstance()->PlayMusicTrack(0, -1);

	MenuBackground = new Background(texturesID::BACKGROUND, Vector2D(0, 720), true);

	bool IsMenu = true;
	double frameTime = (double)1000 / 60;
	while (IsMenu)
	{
		ft.StartClock();

		FPSText->SetWidthAndHeightByText();
		FPSText->Update(100);

		MenuBackground->Update(FrameTimer::DeltaTime());
		MenuBackground->Draw();
		TextureManager::GetInstance()->Draw(texturesID::MENU, SDL_Rect{ 0,0,SCREENWIDTH, SCREENHEIGHT }, One);
		FPSText->Draw(One);

		Renderer::GetInstance()->ClearAndPresent();

		if (!Input::GetInstance()->Update())
		{
			IsMenu = false;
			Quit();
		}
		if (Input::GetInstance()->ButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_A))
		{
			TwoPlayers = false;
			IsMenu = false;
		}
		else if (Input::GetInstance()->ButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_X))
		{
			TwoPlayers = true;
			IsMenu = false;
		}

		ft.EndClock();
		ft.DelayByFrameTime();

		FPSText->SetText(std::to_string(FrameTimer::Frames()));
	}
}

//Creates a fading texture
SDL_Texture* Application::EndGameFadeTexture()
{
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, 32, 0, 0, 0, 0);

	Uint32 colour = SDL_MapRGBA(tempSurface->format, 0, 0, 0, 0);

	SDL_FillRect(tempSurface, NULL, colour);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), tempSurface);

	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr;

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, 150);

	return texture;
}

void Application::Destroy()
{
	//Singletons
	TextureManager::GetInstance()->Clean();
	UIManager::GetInstance()->Clean();
	AudioManager::GetInstance()->Clean();
	Input::GetInstance()->Clean();

	Renderer::GetInstance()->Destroy();

	Input::GetInstance()->DestroyInput();

	if (MenuBackground != nullptr)
	{
		delete MenuBackground;
		MenuBackground = nullptr;
	}

	if (cannon.size() > 0)
	{
		for (int i = 0; i < cannon.size(); i++)
		{
			delete cannon[i];
			cannon[i] = nullptr;
		}
		cannon.clear();
	}

#if _DEBUG
	file.close();
#endif

	SDL_Quit();
}

void Application::Quit()
{
	Running = false;
}
