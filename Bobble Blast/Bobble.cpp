#include "Bobble.h"
#include "CollisionHandler.h"
#include "AudioManager.h"


bool Bobble::RandInit = false;

Bobble::Bobble(Vector2D startPos)
{
	//Init Random seeed
	if (!RandInit)
	{
		srand((unsigned int)time(NULL));
		RandInit = true;
	}

	//assign start pos to both bubble and collider, and scale
	transform->position = startPos;
	circleCollider.SetPos(startPos);
	transform->scale = transform->scale * 2.0f;
	
	//initialize Velocity and speed
	Velocity = Zero;
	speed = 500.0f;

	isFired = false;
	canExplode = false;
	colour = static_cast<Colour>(rand() % (int)Colour::Purple);

	//Animations
	Anim = new Animation();
	Anim->SetProp(texturesID::IDLE_BOBBLE, true, (int)colour, 10, (int)Colour::ALL_COLOURS, 20);
	Anim->SetProp(texturesID::BLOW_BOBBLE, false, (int)colour, 7, (int)Colour::ALL_COLOURS, 10);

	//set the width and height of the bobble
	Anim->WidthAndHeightTexture(texturesID::IDLE_BOBBLE, dstRect);

	//set circle collider size
	circleCollider.SetSize(((float)dstRect.h * transform->scale.y) / 2);
}

void Bobble::StopFire()
{
	isFired = false;
}

void Bobble::ChangeColour(int changeValue)
{
	//Set colour
	colour = static_cast<Colour>((int)colour + changeValue);

	//Check the colour is in the range
	if (colour > Colour::Orange)
		colour = Colour::Black;
	else if (colour < Colour::Black)
		colour = Colour::Orange;
	
	//Set animation's prop based on the colour
	Anim->SetProp(texturesID::IDLE_BOBBLE, true, (int)colour, 10, (int)Colour::ALL_COLOURS, 20);
	Anim->SetProp(texturesID::BLOW_BOBBLE, false, (int)colour, 7, (int)Colour::ALL_COLOURS, 10);
}

Bobble::~Bobble()
{
	Clean();
}


void Bobble::Update(float dt)
{
	//Motion
	if (isFired)
	{
		transform->Translate(Velocity * speed * dt);
		circleCollider.SetPos(transform->position);
	}

	//Updates Animation
	if (!canExplode)
		Anim->Update(texturesID::IDLE_BOBBLE, dt);
	else
		if (Anim->Update(texturesID::BLOW_BOBBLE, dt))
			canDestroy = true;
}

void Bobble::Draw()
{
	AnimationStateMachine();

#if _DEBUG //Prints the bobble's radius (line)
	Vector2D norm(transform->position.x + circleCollider.GetCircle().r * cos(5*PI/3), transform->position.y + circleCollider.GetCircle().r * sin( 5*PI/3 ));
	SDL_RenderDrawLine(Renderer::GetInstance()->GetRenderer(), transform->position.x, transform->position.y, norm.x, norm.y);
#endif
}

void Bobble::Clean()
{
	if (Anim != nullptr)
	{
		delete Anim;
		Anim = nullptr;
	}
}

void Bobble::AnimationStateMachine()
{
	if (canExplode) //Blow
	{
		Anim->WidthAndHeightTexture(texturesID::BLOW_BOBBLE, dstRect);

		dstRect.x = round(transform->position.x - ((float)dstRect.h * transform->scale.y) / 2);
		dstRect.y = round(transform->position.y - ((float)dstRect.h * transform->scale.y) / 2);

		Anim->Draw(texturesID::BLOW_BOBBLE, dstRect, transform->scale);
	}
	else //Idle
	{
		Anim->WidthAndHeightTexture(texturesID::IDLE_BOBBLE, dstRect);
		
		dstRect.x = round(transform->position.x - ((float)dstRect.h * transform->scale.y) / 2);
		dstRect.y = round(transform->position.y - ((float)dstRect.h * transform->scale.y) / 2);

		Anim->Draw(texturesID::IDLE_BOBBLE, dstRect, transform->scale);
	}
}

bool Bobble::CollisionsWithWall(SDL_Rect wall)
{
	if (CollisionHandler::GetInstance()->CircleToBoxCollision(circleCollider.GetCircle(), wall, SurfacePoint))
	{
		Vector2D Normal = transform->position - SurfacePoint; //Surface normal (vector subtraction)

		Normal.Normal(Zero); //Normalize vector

		Bounce(Normal);

		return true;
	}
	
	return false;
}

bool Bobble::CollisionsWithBall(Circle ball)
{
	if (CollisionHandler::GetInstance()->CircleToCircleCollision(circleCollider.GetCircle(), ball))
	{
		return true;
	}

	return false;
}

void Bobble::Bounce(Vector2D Normal)
{
	//Reflection formula
	//reflect = velocity - 2*(v DOT normal) * normal
	Velocity = Velocity - Normal * (2 * Velocity.Dot(Normal));
}

void Bobble::Fire()
{
	isFired = true;
}
