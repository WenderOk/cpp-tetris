#pragma once

class Game;

class GameState
{
public:
    virtual ~GameState() = default;
    virtual void handleInput(Game& game) = 0;
    virtual void update(Game& game, double deltaTime) = 0;
    virtual void render(const Game& game) const = 0;
};