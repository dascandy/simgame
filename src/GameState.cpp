#include "GameState.h"

GameState::GameState() 
: map(32, 32)
, dispatcher(&collisionConfiguration)
, dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration)
{
}

