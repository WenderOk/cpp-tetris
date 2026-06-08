#pragma once

#include "Field.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "GameState.h"
#include <memory>

class Game
{
    Field field;
    Renderer renderer;
    InputHandler inputHandler;
    bool isRunning;
    std::unique_ptr<GameState> currentState;
    std::unique_ptr<GameState> nextState;
public:
    Game();
    void run();
    void setState(std::unique_ptr<GameState>  newState);

    void stop()
    { isRunning = false; }
    
    Field& getField()
    { return field; }
    const Field& getField() const
    { return field; }

    Renderer& getRenderer()
    { return renderer; }
    const Renderer& getRenderer() const
    { return renderer; }

    InputHandler& getInput()
    { return inputHandler; }
    const InputHandler& getInput() const
    { return inputHandler; }
};
