#include "Cannon.h"
#include "Input.h"
#include "TextureManager.h"
#include "AudioManager.h"


Cannon::Cannon(Vector2D p_pos, int p_whatPlayer)
{
	WhatPlayer = p_whatPlayer;

	//secondary transform for the cannon 
	CannonT = new Transform();
	
	//Rotation 
	minRot = -1.35f;
	maxRot = 1.35f;
	rotationSpeed = 100;

	//Setpos
	transform->position = CannonT->position = p_pos;
	//Setting scaling
	transform->scale = transform->scale * 1.5f;
	
	//Get cannon w and h
	SDL_QueryTexture(TextureManager::GetInstance()->GetTextureMap()[texturesID::CANNON], NULL, NULL, &canRect.w, &canRect.h);

	//Set rot point for the arrow
	SDL_QueryTexture(TextureManager::GetInstance()->GetTextureMap()[texturesID::ARROW], NULL, NULL, &arrowRect.w, &arrowRect.h);
	rotPoint.x = arrowRect.w * transform->scale.x / 2;		rotPoint.y = arrowRect.h * transform->scale.y / 2;


	//Rot pivot
	Vector2D p2(transform->position.x + ((canRect.w * CannonT->scale.x) / 2), transform->position.y + (canRect.h * CannonT->scale.y)/2);
	RotationPos = p2;

	canRect.x = RotationPos.x - (canRect.w * CannonT->scale.x) / 2;
	canRect.y = RotationPos.y - (canRect.h * CannonT->scale.y) / 2;

	//Set Direction point -->
	float s = sin(transform->GetAngle());
	float c = cos(transform->GetAngle());

	Direction.x = c * (transform->position.x + ((canRect.w * CannonT->scale.x)/2) - RotationPos.x) - s * (transform->position.y - RotationPos.y) + RotationPos.x;
	Direction.y = s * (transform->position.x + ((canRect.w * CannonT->scale.x)/2) - RotationPos.x) + c * (transform->position.y - RotationPos.y) + RotationPos.y;

	//Set booble to rot pivot
	bobble = new Bobble(RotationPos);
}

Cannon::~Cannon()
{
	Clean();
}

void Cannon::Update(float dt)
{
	if (bobble != nullptr && bobble->CanDestroy())
	{
		delete bobble;
		bobble = nullptr;
	}

	//Rotate the cannon
	if (!gameOver)
	{
		if (Input::GetInstance()->ButtonHeld((Players)WhatPlayer, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			transform->Rotate(-rotationSpeed * dt);
			transform->angle = UsefullFunctions::Clamp(transform->GetAngle(), minRot, maxRot);

			float s = sin(transform->GetAngle());
			float c = cos(transform->GetAngle());

			Direction.x = c * (transform->position.x + ((canRect.w * CannonT->scale.x) / 2) - RotationPos.x) - s * (transform->position.y - RotationPos.y) + RotationPos.x;
			Direction.y = s * (transform->position.x + ((canRect.w * CannonT->scale.x) / 2) - RotationPos.x) + c * (transform->position.y - RotationPos.y) + RotationPos.y;

		}
		if (Input::GetInstance()->ButtonHeld((Players)WhatPlayer, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			transform->Rotate(rotationSpeed * dt);
			transform->angle = UsefullFunctions::Clamp(transform->GetAngle(), minRot, maxRot);

			float s = sin(transform->GetAngle());
			float c = cos(transform->GetAngle());

			Direction.x = c * (transform->position.x + ((canRect.w * CannonT->scale.x) / 2) - RotationPos.x) - s * (transform->position.y - RotationPos.y) + RotationPos.x;
			Direction.y = s * (transform->position.x + ((canRect.w * CannonT->scale.x) / 2) - RotationPos.x) + c * (transform->position.y - RotationPos.y) + RotationPos.y;
		}

		if (bobble != nullptr)
		{
			//Change colour
			if (Input::GetInstance()->ButtonPressed((Players)WhatPlayer, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) && !bobble->IsFiring() && !bobble->CanExplode())
			{
				bobble->ChangeColour(-1);
			}
			if (Input::GetInstance()->ButtonPressed((Players)WhatPlayer, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) && !bobble->IsFiring() && !bobble->CanExplode())
			{
				bobble->ChangeColour(1);
			}

			//Shoot 
			if (Input::GetInstance()->ButtonPressed((Players)WhatPlayer, SDL_CONTROLLER_BUTTON_A) && !bobble->IsFiring())
			{
				Vector2D normal = Direction - RotationPos;
				bobble->SetVelocity(normal.Normal(Zero));
				bobble->Fire();

				AudioManager::GetInstance()->PlaySFX(3, 0, 0);
			}

			//Return to cannon
			if (bobble != nullptr && bobble->GetCircle().pos.y < 0)
			{
				bobble->StopFire();
				bobble->SetPosition(RotationPos);
			}

			if (bobble != nullptr) bobble->Update(dt);
		}
		//Instantiate new bobble if nullptr
		else
			bobble = new Bobble(RotationPos);
	}
}

void Cannon::Draw()
{
#if _DEBUG
	SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
#endif

	//Get destRect x and y from the rotation point 
	Vector2D arrow( RotationPos.x - (arrowRect.w * transform->scale.x) / 2, RotationPos.y - (arrowRect.h * transform->scale.y) / 2);

	//Draw cannon and arrow
	TextureManager::GetInstance()->Draw(texturesID::CANNON, canRect, CannonT->scale);
	TextureManager::GetInstance()->DrawRotate(texturesID::ARROW, arrow, transform->scale,
		transform->GetAngle() / (PI / 180), rotPoint);
	
#if _DEBUG
	SDL_RenderDrawLine(Renderer::GetInstance()->GetRenderer(), RotationPos.x, RotationPos.y, Direction.x, Direction.y);
#endif

	//Draw bobble
	if (bobble != nullptr) bobble->Draw();
}

void Cannon::Clean()
{
	if (bobble != nullptr)
	{
		delete bobble;
		bobble = nullptr;
	}
	if (CannonT != nullptr)
	{
		delete CannonT;
		CannonT = nullptr;
	}
}
