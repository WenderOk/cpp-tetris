#include "Game.h"
#include "GameState.h"
#include "PlayingState.h"
#include <chrono>
#include <memory>
#include <utility>

Game::Game()
{ setState(std::make_unique<PlayingState>()); }

void Game::setState(std::unique_ptr<GameState> newState)
{ currentState = std::move(newState); }

void Game::run()
{
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

    while (currentState != nullptr) 
    {
        std::chrono::steady_clock::time_point currentTime{ std::chrono::steady_clock::now() };
        double deltaTime{ std::chrono::duration<double>(currentTime - lastTime).count() };
        lastTime = currentTime;

        currentState->handleInput(*this);

        currentState->update(*this, deltaTime);

        currentState->render(*this);

        inputHandler.sleepMillis(10);
    
    }
}