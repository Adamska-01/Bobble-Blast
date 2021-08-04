#include "CollisionHandler.h"

CollisionHandler* CollisionHandler::Instance = nullptr;

bool CollisionHandler::BoxToBoxCollision(SDL_Rect A, SDL_Rect B)
{
    //Sides of the rectangle 
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;


    //Check collisions
    if (bottomA <= topB)
        return false;
    if (topA >= bottomB)
        return false;
    if (rightA <= leftB)
        return false;
    if (leftA >= rightB)
        return false;

    return true; //collision happened
}

bool CollisionHandler::CircleToBoxCollision(Circle A, SDL_Rect B, Vector2D& P)
{
    //Closest points on collision box
    Vector2D p;

    //Find closest x offset
    if (A.pos.x < B.x)
        p.x = B.x;
    else if (A.pos.x > B.x + B.w)
        p.x = B.x + B.w;
    else
        p.x = A.pos.x;

    //Find closest y offset
    if (A.pos.y < B.y)
        p.y = B.y;
    else if (A.pos.y > B.y + B.h)
        p.y = B.y + B.h;
    else
        p.y = A.pos.y;

    P = p; //Set collision point (needed for the surface normal (bounce))

    //Check if the point is inside the circle
    if (A.pos.dist(p) < A.r)
        return true;

    return false; //No collision
}

bool CollisionHandler::CircleToCircleCollision(Circle A, Circle B)
{
    //Check if the point is touching the circle
    if (A.pos.dist(B.pos) <= A.r + B.r)
        return true;

    return false; //No collision
}
