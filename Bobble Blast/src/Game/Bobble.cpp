#include "../../include/Components/Collisions/CollisionHandler.h"
#include "../../include/Components/SpriteAnimator.h"
#include "../../include/Components/Transform.h"
#include "../../include/Core/SDL/Renderer.h"
#include "../../include/Game/Bobble.h"
#include "../../include/Math/MathConstants.h"


bool Bobble::RandInit = false;


Bobble::Bobble(Vector2 startPos)
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
	Velocity = Vector2::Zero;
	speed = 500.0f;

	isFired = false;
	canExplode = false;
	colour = static_cast<Colour>(rand() % (int)Colour::Purple);

	//Animations
	Anim = new SpriteAnimator();
	Anim->SetProp(texturesID::IDLE_BOBBLE, true, (int)colour, 10, (int)Colour::ALL_COLOURS, 20);
	Anim->SetProp(texturesID::BLOW_BOBBLE, false, (int)colour, 7, (int)Colour::ALL_COLOURS, 10);

	//set the width and height of the bobble
	dstRect = Anim->GetFrameRect(texturesID::IDLE_BOBBLE);

	//set circle collider size
	circleCollider.SetSize(((float)dstRect.h * transform->scale.y) / 2);
}

void Bobble::StopFire()
{
	isFired = false;
}

void Bobble::SetVelocity(Vector2 v)
{
	Velocity = v;
}

void Bobble::SetPosition(Vector2 v)
{
	transform->position = v;
	circleCollider.SetPos(v);
}

void Bobble::SetDestruction(bool value)
{
	canExplode = value;
}

void Bobble::SetSpeed(float value)
{
	speed = value;
}

Circle Bobble::GetCircle()
{
	return circleCollider.GetCircle();
}

bool Bobble::CanDestroy()
{
	return canDestroy;
}

bool Bobble::CanExplode()
{ 
	return canExplode; 
}

bool Bobble::IsFiring()
{ 
	return isFired; 
}

Colour Bobble::GetColor()
{ 
	return colour; 
}

void Bobble::ChangeColour(int changeValue)
{
	//Set colour
	colour = static_cast<Colour>((int)colour + changeValue);

	//Check the colour is in the range
	if (colour > Colour::Orange)
	{
		colour = Colour::Black;
	}
	else if (colour < Colour::Black)
	{
		colour = Colour::Orange;
	}

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
	Vector2 norm(transform->position.x + circleCollider.GetCircle().radius * cos(5 * MathConstants::PI / 3), transform->position.y + circleCollider.GetCircle().radius * sin( 5 * MathConstants::PI / 3 ));
	SDL_RenderDrawLine(Renderer::GetInstance()->GetRenderer(), transform->position.x, transform->position.y, norm.x, norm.y);
#endif
}

void Bobble::Clean()
{
	if (Anim == nullptr)
		return;

	delete Anim;
	Anim = nullptr;
}

void Bobble::AnimationStateMachine()
{
	auto texID = canExplode ? texturesID::BLOW_BOBBLE : texturesID::IDLE_BOBBLE;

	dstRect = Anim->GetFrameRect(texID);

	dstRect.x = round(transform->position.x - ((float)dstRect.h * transform->scale.y) / 2);
	dstRect.y = round(transform->position.y - ((float)dstRect.h * transform->scale.y) / 2);

	Anim->Draw(texID, dstRect, transform->scale);
}

bool Bobble::CollisionsWithWall(SDL_Rect wall)
{
	if (CollisionHandler::CircleToBoxCollision(circleCollider.GetCircle(), wall, SurfacePoint))
	{
		auto Normal = transform->position - SurfacePoint; //Surface normal (vector subtraction)

		Normal.Normalize(); //Normalize vector

		Bounce(Normal);

		return true;
	}
	
	return false;
}

bool Bobble::CollisionsWithBall(Circle ball)
{
	return CollisionHandler::CircleToCircleCollision(circleCollider.GetCircle(), ball);
}

void Bobble::Bounce(Vector2 Normal)
{
	//Reflection formula
	//reflect = velocity - 2*(v DOT normal) * normal
	Velocity = Velocity - Normal * (2 * Velocity.Dot(Normal));
}

void Bobble::Fire()
{
	isFired = true;
}