#pragma once

#include "Field.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "GameState.h"

class Game
{
    Field field;
    Renderer renderer;
    InputHandler inputHandler;
    GameState* currentState;
public:
    void run();
    void setState(GameState newState);
    Field& getField();
    Renderer& getRenderer();
    InputHandler& getInputHandler();
};
