#pragma once

#include "Game.h"
#include "InputHandler.h"
#include "Renderer.h"

class GameState
{
    virtual void handleInput(Game&, InputHandler&) = 0;
    virtual void update(Game&, double deltaTime) = 0;
    virtual void renderer(Game&, Renderer&) = 0;

};